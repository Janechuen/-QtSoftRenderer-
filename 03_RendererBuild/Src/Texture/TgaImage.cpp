#include <iostream>
#include <cstring>
#include "tgaimage.h"

TGAImage::TGAImage(const int w, const int h, const int bpp) : w(w), h(h), bpp(bpp), data(w* h* bpp, 0) {}

bool TGAImage::read_tga_file(const std::string filename) {
	std::ifstream in;
	/*���ȣ�ͨ�� std::ifstream ��� open() ������ָ�����ļ�����
	��ʹ�� std::ios::binary ��־�Զ�����ģʽ���ж�ȡ������ļ��޷��򿪣������������Ϣ������ false��*/
	in.open(filename, std::ios::binary);
	if (!in.is_open()) {
		std::cerr << "can't open file " << filename << "\n";
		return false;
	}
	/*���ţ�������һ�� TGAHeader �ṹ����� header�����ڴ洢��ȡ���� TGA �ļ�ͷ��Ϣ��ʹ�� in.read() �������ļ�ͷ���ݶ�ȡ�� 
	header �����У���ʹ�� sizeof(header) ��ָ����ȡ���ֽ����������ȡ�ļ�ͷʧ�ܣ������������Ϣ������ false��*/
	TGAHeader header;
	in.read(reinterpret_cast<char*>(&header), sizeof(header));
	if (!in.good()) {
		std::cerr << "an error occured while reading the header\n";
		return false;
	}
	/*�����������ݶ�ȡ�����ļ�ͷ��Ϣ���� TGAImage ����ĳ�Ա���� w��h��bpp�����У�header.width �洢��ͼ��Ŀ�ȣ�header.height 
	�洢��ͼ��ĸ߶ȣ�header.bitsperpixel �洢��ÿ�����ص�λ��ȡ�ͨ��λ�Ʋ�������>>���� header.bitsperpixel ��ֵת��Ϊ�ֽڵ�λ��
	����ֵ�� TGAImage ����ĳ�Ա���� bpp��ͬʱ�����ͼ��Ŀ�Ⱥ͸߶��Ƿ�����㣬����λ����Ƿ�Ϊ�Ϸ���ֵ��GRAYSCALE��RGB��RGBA��
	����������������������������Ϣ������ false��*/
	w = header.width;
	h = header.height;
	bpp = header.bitsperpixel >> 3;
	if (w <= 0 || h <= 0 || (bpp != GRAYSCALE && bpp != RGB && bpp != RGBA)) {
		std::cerr << "bad bpp (or width/height) value\n";
		return false;
	}
	/*���ţ����ݼ���õ���ͼ�����ݴ�С��bpp * w * h������һ�� std::vectorstd::uint8_t ���͵� data ����������ʼ��Ϊȫ�㣬
	����ʼʱͼ������Ϊ�ա�*/
	size_t nbytes = bpp * w * h;
	data = std::vector<std::uint8_t>(nbytes, 0);
	/*�������������ļ�ͷ�� datatypecode �ֶε�ֵ��ѡ��ͬ�Ķ�ȡ��ʽ����� datatypecode Ϊ 3 �� 2����ʾͼ�����ݲ��÷�ѹ���ķ�ʽ�洢��
	ֱ��ʹ�� in.read() ������ͼ�����ݶ�ȡ�� data �����У�������ȡ�Ƿ�ɹ��������ȡʧ�ܣ������������Ϣ������ false��*/
	if (3 == header.datatypecode || 2 == header.datatypecode) {
		in.read(reinterpret_cast<char*>(data.data()), nbytes);
		if (!in.good()) {
			std::cerr << "an error occured while reading the data\n";
			return false;
		}
	}
	/*��� datatypecode Ϊ 10 �� 11����ʾͼ�����ݲ����� RLE ѹ����ʽ�洢������ load_rle_data() �����������ͼ��� RLE ѹ����ͼ�����ݡ�
	��� load_rle_data() �������� false����ʾ�����ͼ���ʧ�ܣ������������Ϣ������ false��*/
	else if (10 == header.datatypecode || 11 == header.datatypecode) {
		if (!load_rle_data(in)) {
			std::cerr << "an error occured while reading the data\n";
			return false;
		}
	}
	/*��� datatypecode �������ϼ�����֪��ֵ����ʾ�ļ���ʽδ֪�����������Ϣ������ false��*/
	else {
		std::cerr << "unknown file format " << (int)header.datatypecode << "\n";
		return false;
	}
	/*��󣬸����ļ�ͷ�� imagedescriptor �ֶε�ֵ�������Ƿ���Ҫ��ֱ��תͼ��0x20 ��ʾ��ֱ��ת�����Լ��Ƿ���Ҫˮƽ��תͼ��0x10 ��ʾˮƽ��ת��
	��������ͼ��Ŀ�ȡ��߶Ⱥ�λ��ȣ������� true ��ʾ��ȡ�ͼ���ͼ��ɹ���*/
	if (!(header.imagedescriptor & 0x20))
		flip_vertically();
	if (header.imagedescriptor & 0x10)
		flip_horizontally();
	std::cerr << w << "x" << h << "/" << bpp * 8 << "\n";
	return true;
}

bool TGAImage::load_rle_data(std::ifstream& in) {
	size_t pixelcount = w * h;//ͼ���������������ͼ��Ŀ�� w ����ͼ��ĸ߶� h
	size_t currentpixel = 0;//��ǰ�Ѿ���ȡ������������ʼֵΪ 0
	size_t currentbyte = 0;//��ǰ�Ѿ���ȡ���ֽ�������ʼֵΪ 0
	TGAColor colorbuffer;//�����ݴ��ȡ����ɫֵ�Ļ�����������Ϊ TGAColor�����ܰ�������ֽڣ������ֽ����� bpp ����
	//����ͨ��һ�� do-while ѭ�������϶�ȡ�ļ����е��ֽ����ݣ�������ÿ���ֽڵ�ֵ��Ϊѹ�����ͷ����Ϣ��
	do {
		/*��ѭ���ڲ������ȶ�ȡһ���ֽ���Ϊ chunkheader����ʾѹ�����ͷ����Ϣ��
		�����ȡ�ֽ�ʧ�ܣ�in.good() ���� false���������������Ϣ������ false��*/
		std::uint8_t chunkheader = 0;
		chunkheader = in.get();
		if (!in.good()) {
			std::cerr << "an error occured while reading the data\n";
			return false;
		}
		/*Ȼ�󣬸��� chunkheader ��ֵ���ж�ѹ�����Ƿ�ѹ�����������ݻ���ѹ�����������ݡ�
		��� chunkheader С�� 128����ʾ�������� chunkheader + 1 ���ֽ��Ƿ�ѹ�����������ݡ�
		ѭ�� chunkheader + 1 �Σ�ÿ�ζ�ȡ bpp ���ֽڵ���ɫֵ��������洢�� TGAImage ����� data ��Ա�У�
		ͬʱ���� currentbyte �� currentpixel ��ֵ����� currentpixel ���� pixelcount�������������Ϣ������ false��*/
		if (chunkheader < 128) {
			chunkheader++;
			for (int i = 0; i < chunkheader; i++) {
				in.read(reinterpret_cast<char*>(colorbuffer.bgra), bpp);
				if (!in.good()) {
					std::cerr << "an error occured while reading the header\n";
					return false;
				}
				for (int t = 0; t < bpp; t++)
					data[currentbyte++] = colorbuffer.bgra[t];
				currentpixel++;
				if (currentpixel > pixelcount) {
					std::cerr << "Too many pixels read\n";
					return false;
				}
			}
		}
		/*��� chunkheader ���ڵ��� 128����ʾ���������ֽ�������ѹ�����������ݡ��� chunkheader - 127 ��ֵ��Ϊ�ظ�������
		��ȡ bpp ���ֽڵ���ɫֵ���������ظ��洢 chunkheader - 127 �ε� TGAImage ����� data ��Ա�У�ͬʱ���� currentbyte
		�� currentpixel ��ֵ����� currentpixel ���� pixelcount�������������Ϣ������ false��*/
		else {
			chunkheader -= 127;
			in.read(reinterpret_cast<char*>(colorbuffer.bgra), bpp);
			if (!in.good()) {
				std::cerr << "an error occured while reading the header\n";
				return false;
			}
			for (int i = 0; i < chunkheader; i++) {
				for (int t = 0; t < bpp; t++)
					data[currentbyte++] = colorbuffer.bgra[t];
				currentpixel++;
				if (currentpixel > pixelcount) {
					std::cerr << "Too many pixels read\n";
					return false;
				}
			}
		}
	}
	/*���ѭ������ֱ�� currentpixel ���� pixelcount����ʾ���е����������Ѿ��ɹ���ȡ����ѹ������ʱ���� true ��ʾ���سɹ���
	�������÷���������ȷ�ؽ��� TGA �ļ��о��� RLE ѹ�����������ݣ�������洢�� TGAImage �����У��Թ����������ʹ�á�*/
	while (currentpixel < pixelcount);
	return true;
}

bool TGAImage::write_tga_file(const std::string filename, const bool vflip, const bool rle) const {
	constexpr std::uint8_t developer_area_ref[4] = { 0, 0, 0, 0 };
	constexpr std::uint8_t extension_area_ref[4] = { 0, 0, 0, 0 };
	constexpr std::uint8_t footer[18] = { 'T','R','U','E','V','I','S','I','O','N','-','X','F','I','L','E','.','\0' };
	std::ofstream out;
	out.open(filename, std::ios::binary);
	if (!out.is_open()) {
		std::cerr << "can't open file " << filename << "\n";
		return false;
	}
	TGAHeader header = {};
	header.bitsperpixel = bpp << 3;
	header.width = w;
	header.height = h;
	header.datatypecode = (bpp == GRAYSCALE ? (rle ? 11 : 3) : (rle ? 10 : 2));
	header.imagedescriptor = vflip ? 0x00 : 0x20; // top-left or bottom-left origin
	out.write(reinterpret_cast<const char*>(&header), sizeof(header));
	if (!out.good()) {
		std::cerr << "can't dump the tga file\n";
		return false;
	}
	if (!rle) {
		out.write(reinterpret_cast<const char*>(data.data()), w * h * bpp);
		if (!out.good()) {
			std::cerr << "can't unload raw data\n";
			return false;
		}
	}
	else if (!unload_rle_data(out)) {
		std::cerr << "can't unload rle data\n";
		return false;
	}
	out.write(reinterpret_cast<const char*>(developer_area_ref), sizeof(developer_area_ref));
	if (!out.good()) {
		std::cerr << "can't dump the tga file\n";
		return false;
	}
	out.write(reinterpret_cast<const char*>(extension_area_ref), sizeof(extension_area_ref));
	if (!out.good()) {
		std::cerr << "can't dump the tga file\n";
		return false;
	}
	out.write(reinterpret_cast<const char*>(footer), sizeof(footer));
	if (!out.good()) {
		std::cerr << "can't dump the tga file\n";
		return false;
	}
	return true;
}

// TODO: it is not necessary to break a raw chunk for two equal pixels (for the matter of the resulting size)
bool TGAImage::unload_rle_data(std::ofstream& out) const {
	const std::uint8_t max_chunk_length = 128;
	size_t npixels = w * h;
	size_t curpix = 0;
	while (curpix < npixels) {
		size_t chunkstart = curpix * bpp;
		size_t curbyte = curpix * bpp;
		std::uint8_t run_length = 1;
		bool raw = true;
		while (curpix + run_length < npixels && run_length < max_chunk_length) {
			bool succ_eq = true;
			for (int t = 0; succ_eq && t < bpp; t++)
				succ_eq = (data[curbyte + t] == data[curbyte + t + bpp]);
			curbyte += bpp;
			if (1 == run_length)
				raw = !succ_eq;
			if (raw && succ_eq) {
				run_length--;
				break;
			}
			if (!raw && !succ_eq)
				break;
			run_length++;
		}
		curpix += run_length;
		out.put(raw ? run_length - 1 : run_length + 127);
		if (!out.good()) {
			std::cerr << "can't dump the tga file\n";
			return false;
		}
		out.write(reinterpret_cast<const char*>(data.data() + chunkstart), (raw ? run_length * bpp : bpp));
		if (!out.good()) {
			std::cerr << "can't dump the tga file\n";
			return false;
		}
	}
	return true;
}

TGAColor TGAImage::get(const int x, const int y) const {
	if (!data.size() || x < 0 || y < 0 || x >= w || y >= h)
		return {};
	TGAColor ret = { 0, 0, 0, 0, bpp };
	const std::uint8_t* p = data.data() + (x + y * w) * bpp;
	for (int i = bpp; i--; ret.bgra[i] = p[i]);
	return ret;
}

void TGAImage::set(int x, int y, const TGAColor& c) {
	if (!data.size() || x < 0 || y < 0 || x >= w || y >= h) return;
	memcpy(data.data() + (x + y * w) * bpp, c.bgra, bpp);
}

void TGAImage::flip_horizontally() {
	int half = w >> 1;
	for (int i = 0; i < half; i++)
		for (int j = 0; j < h; j++)
			for (int b = 0; b < bpp; b++)
				std::swap(data[(i + j * w) * bpp + b], data[(w - 1 - i + j * w) * bpp + b]);
}

void TGAImage::flip_vertically() {
	int half = h >> 1;
	for (int i = 0; i < w; i++)
		for (int j = 0; j < half; j++)
			for (int b = 0; b < bpp; b++)
				std::swap(data[(i + j * w) * bpp + b], data[(i + (h - 1 - j) * w) * bpp + b]);
}

int TGAImage::width() const {
	return w;
}

int TGAImage::height() const {
	return h;
}


