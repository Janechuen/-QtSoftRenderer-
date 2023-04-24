#pragma once
#include <string>
#include <Core.h>
class FrameBuffer
{
public:
	FrameBuffer(int w, int h) :Width(w), Height(h) {};
	~FrameBuffer() {};
	std::string Name; //窗口名称
	unsigned char* GetColorBuffer();//获取私有变量 colorbuffer
	void InitFrameBuffer(vec4 vec);
	void UpdataFrameBuffer(int x, int y, vec4 vec);
private:
	unsigned char colorbuffer[8294400];//记录了一个渲染窗口的像素总数 比如 1920X1080X4像素的窗口的像素总数为8294405个
	int Width; //定义画布的宽度
	int Height; //定义画布的高
	//unsigned char colorbuffer[Width*Height*4];

};




