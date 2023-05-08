#include "FrameBuffer.h"

unsigned char* FrameBuffer::GetColorBuffer()
{
	return colorbuffer;
}
void FrameBuffer::InitFrameBuffer(vec4 vec)
{
	//初始化FrameBuffer 颜色 扫描宽度高度像素内RGBA信息 并且赋予对应的信息
	unsigned char cl[4];
	cl[0] = static_cast<unsigned char>(vec.x * 255);
	cl[1] = static_cast<unsigned char>(vec.y * 255);
	cl[2] = static_cast<unsigned char>(vec.z * 255);
	cl[3] = static_cast<unsigned char>(vec.w * 255);
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
		        for (int k = 0; k < 4; k++) {
					//xyzw 向量是横向排布的 I*width获取行数 j代表在当前行的像素个数
		            colorbuffer[(i * Width + j) * 4 + k] = cl[k];
			}
		}
	}
}
void FrameBuffer::UpdataFrameBuffer(int x , int y ,vec4 vec)
{
	//接收顶点的位置信息 XY 通过传入的值设置FrameBuffer的颜色
	unsigned char cl[4];
	//cl[0] = static_cast<unsigned char>(vec.x * 255);
	//cl[1] = static_cast<unsigned char>(vec.y * 255);
	//cl[2] = static_cast<unsigned char>(vec.z * 255);
	//cl[3] = static_cast<unsigned char>(vec.w * 255);
	cl[0] = static_cast<unsigned char>(1 * 255);
	cl[1] = static_cast<unsigned char>(0 * 255);
	cl[2] = static_cast<unsigned char>(0 * 255);
	cl[3] = static_cast<unsigned char>(0 * 255);
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

