#pragma once
#include <string>
#include <Core.h>
class FrameBuffer
{
public:
	FrameBuffer(int w, int h) :Width(w), Height(h) {};
	~FrameBuffer() {};
	std::string Name; //��������
	unsigned char* GetColorBuffer();//��ȡ˽�б��� colorbuffer
	double GetDepthBuffer(int x,int y);
	void InitFrameBuffer(vec4 vec);
	void InitDepthBuffer(double z);
	void UpdataFrameBuffer(int x, int y, vec4 vec);
	void UpdataDepthBuffer(int x, int y, double z);
private:
	unsigned char colorbuffer[8294400];//��¼��һ����Ⱦ���ڵ��������� ���� 1920X1080X4���صĴ��ڵ���������Ϊ8294405��
	double Zbuffer[8294400];
	int Width; //���廭���Ŀ��
	int Height; //���廭���ĸ�
	//unsigned char colorbuffer[Width*Height*4];

};




