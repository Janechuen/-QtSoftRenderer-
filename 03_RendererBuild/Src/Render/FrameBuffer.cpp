#include "FrameBuffer.h"

unsigned char* FrameBuffer::GetColorBuffer()
{
	return colorbuffer;
}

double FrameBuffer::GetDepthBuffer(int x, int y)
{
	 return  Zbuffer[(y * Width + x) * 4 ];
	
}


void FrameBuffer::InitFrameBuffer(vec4 vec)
{
	//��ʼ��FrameBuffer ��ɫ ɨ���ȸ߶�������RGBA��Ϣ ���Ҹ����Ӧ����Ϣ
	unsigned char cl[4];
	cl[0] = static_cast<unsigned char>(vec.x * 255);
	cl[1] = static_cast<unsigned char>(vec.y * 255);
	cl[2] = static_cast<unsigned char>(vec.z * 255);
	cl[3] = static_cast<unsigned char>(vec.w * 255);
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
		        for (int k = 0; k < 4; k++) {
					//xyzw �����Ǻ����Ų��� I*width��ȡ���� j�����ڵ�ǰ�е����ظ���
		            colorbuffer[(i * Width + j) * 4 + k] = cl[k];
			}
		}
	}
}

void FrameBuffer::InitDepthBuffer(double z)
{
	//��ʼ��FrameBuffer ��ɫ ɨ���ȸ߶�������RGBA��Ϣ ���Ҹ����Ӧ����Ϣ
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			for (int k = 0; k < 4; k++) {
				//xyzw �����Ǻ����Ų��� I*width��ȡ���� j�����ڵ�ǰ�е����ظ���
				Zbuffer[(i * Width + j) * 4 + k] = z;
			}
		}
	}
}

void FrameBuffer::UpdataFrameBuffer(int x , int y ,vec4 vec)
{
	//���ն����λ����Ϣ XY ͨ�������ֵ����FrameBuffer����ɫ
	unsigned char cl[4];
	cl[0] = static_cast<unsigned char>(vec.x * 255);
	cl[1] = static_cast<unsigned char>(vec.y * 255);
	cl[2] = static_cast<unsigned char>(vec.z * 255);
	cl[3] = static_cast<unsigned char>(vec.w * 255);
	for (int k = 0; k < 4; k++) {
		if (x>=Width||y>=Height)
		{
			break;
		} 
		else if (x<0||y<0)
		{
			break;
		}
		else
		{
			colorbuffer[(y * Width + x) * 4 + k] = cl[k];
		}
	}
}

void FrameBuffer::UpdataDepthBuffer(int x, int y, double z)
{
	for (int k = 0; k < 4; k++) 
	{
		if (x >= Width || y >= Height)
		{
			break;
		}
		else if (x < 0 || y < 0)
		{
			break;
		}
		else
		{
			Zbuffer[(y * Width + x) * 4 + k] = z;
		}
		

	}
	
}
