#include <iostream>
#include <cstring>
#include "tgaimage.h"

TGAImage::TGAImage(const int w, const int h, const int bpp) : w(w), h(h), bpp(bpp), data(w* h* bpp, 0) {}

bool TGAImage::read_tga_file(const std::string filename) {
	std::ifstream in;
	/*首先，通过 std::ifstream 类的 open() 方法打开指定的文件名，
	并使用 std::ios::binary 标志以二进制模式进行读取。如果文件无法打开，则输出错误信息并返回 false。*/
	in.open(filename, std::ios::binary);
	if (!in.is_open()) {
		std::cerr << "can't open file " << filename << "\n";
		return false;
	}
	/*接着，定义了一个 TGAHeader 结构体变量 header，用于存储读取到的 TGA 文件头信息。使用 in.read() 方法将文件头数据读取到 
	header 变量中，并使用 sizeof(header) 来指定读取的字节数。如果读取文件头失败，则输出错误信息并返回 false。*/
	TGAHeader header;
	in.read(reinterpret_cast<char*>(&header), sizeof(header));
	if (!in.good()) {
		std::cerr << "an error occured while reading the header\n";
		return false;
	}
	/*接下来，根据读取到的文件头信息更新 TGAImage 对象的成员变量 w、h、bpp。其中，header.width 存储了图像的宽度，header.height 
	存储了图像的高度，header.bitsperpixel 存储了每个像素的位深度。通过位移操作符（>>）将 header.bitsperpixel 的值转换为字节单位，
	并赋值给 TGAImage 对象的成员变量 bpp。同时，检查图像的宽度和高度是否大于零，并且位深度是否为合法的值（GRAYSCALE、RGB、RGBA）
	，如果不满足条件，则输出错误信息并返回 false。*/
	w = header.width;
	h = header.height;
	bpp = header.bitsperpixel >> 3;
	if (w <= 0 || h <= 0 || (bpp != GRAYSCALE && bpp != RGB && bpp != RGBA)) {
		std::cerr << "bad bpp (or width/height) value\n";
		return false;
	}
	/*接着，根据计算得到的图像数据大小（bpp * w * h）创建一个 std::vectorstd::uint8_t 类型的 data 容器，并初始化为全零，
	即初始时图像数据为空。*/
	size_t nbytes = bpp * w * h;
	data = std::vector<std::uint8_t>(nbytes, 0);
	/*接下来，根据文件头的 datatypecode 字段的值，选择不同的读取方式。如果 datatypecode 为 3 或 2，表示图像数据采用非压缩的方式存储，
	直接使用 in.read() 方法将图像数据读取到 data 容器中，并检查读取是否成功。如果读取失败，则输出错误信息并返回 false。*/
	if (3 == header.datatypecode || 2 == header.datatypecode) {
		in.read(reinterpret_cast<char*>(data.data()), nbytes);
		if (!in.good()) {
			std::cerr << "an error occured while reading the data\n";
			return false;
		}
	}
	/*如果 datatypecode 为 10 或 11，表示图像数据采用了 RLE 压缩方式存储，调用 load_rle_data() 方法来解析和加载 RLE 压缩的图像数据。
	如果 load_rle_data() 方法返回 false，表示解析和加载失败，则输出错误信息并返回 false。*/
	else if (10 == header.datatypecode || 11 == header.datatypecode) {
		if (!load_rle_data(in)) {
			std::cerr << "an error occured while reading the data\n";
			return false;
		}
	}
	/*如果 datatypecode 不是以上几种已知的值，表示文件格式未知，输出错误信息并返回 false。*/
	else {
		std::cerr << "unknown file format " << (int)header.datatypecode << "\n";
		return false;
	}
	/*最后，根据文件头的 imagedescriptor 字段的值，决定是否需要垂直翻转图像（0x20 表示垂直翻转），以及是否需要水平翻转图像（0x10 表示水平翻转）
	。最后输出图像的宽度、高度和位深度，并返回 true 表示读取和加载图像成功。*/
	if (!(header.imagedescriptor & 0x20))
		flip_vertically();
	if (header.imagedescriptor & 0x10)
		flip_horizontally();
	std::cerr << w << "x" << h << "/" << bpp * 8 << "\n";
	return true;
}

bool TGAImage::load_rle_data(std::ifstream& in) {
	size_t pixelcount = w * h;//图像的像素总数，即图像的宽度 w 乘以图像的高度 h
	size_t currentpixel = 0;//当前已经读取的像素数，初始值为 0
	size_t currentbyte = 0;//当前已经读取的字节数，初始值为 0
	TGAColor colorbuffer;//用于暂存读取的颜色值的缓冲区，类型为 TGAColor，可能包含多个字节，具体字节数由 bpp 决定
	//代码通过一个 do-while 循环，不断读取文件流中的字节数据，并解析每个字节的值作为压缩块的头部信息。
	do {
		/*在循环内部，首先读取一个字节作为 chunkheader，表示压缩块的头部信息。
		如果读取字节失败（in.good() 返回 false），则输出错误信息并返回 false。*/
		std::uint8_t chunkheader = 0;
		chunkheader = in.get();
		if (!in.good()) {
			std::cerr << "an error occured while reading the data\n";
			return false;
		}
		/*然后，根据 chunkheader 的值，判断压缩块是非压缩的像素数据还是压缩的像素数据。
		如果 chunkheader 小于 128，表示接下来的 chunkheader + 1 个字节是非压缩的像素数据。
		循环 chunkheader + 1 次，每次读取 bpp 个字节的颜色值，并将其存储到 TGAImage 对象的 data 成员中，
		同时更新 currentbyte 和 currentpixel 的值。如果 currentpixel 大于 pixelcount，则输出错误信息并返回 false。*/
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
		/*如果 chunkheader 大于等于 128，表示接下来的字节数据是压缩的像素数据。将 chunkheader - 127 的值作为重复次数，
		读取 bpp 个字节的颜色值，并将其重复存储 chunkheader - 127 次到 TGAImage 对象的 data 成员中，同时更新 currentbyte
		和 currentpixel 的值。如果 currentpixel 大于 pixelcount，则输出错误信息并返回 false。*/
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
	/*最后，循环继续直到 currentpixel 等于 pixelcount，表示所有的像素数据已经成功读取并解压缩，此时返回 true 表示加载成功。
	这样，该方法可以正确地解析 TGA 文件中经过 RLE 压缩的像素数据，并将其存储到 TGAImage 对象中，以供后续处理和使用。*/
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


