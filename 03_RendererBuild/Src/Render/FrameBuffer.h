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
	void InitFrameBuffer(vec4 vec);
	void UpdataFrameBuffer(int x, int y, vec4 vec);
private:
	unsigned char colorbuffer[8294400];//��¼��һ����Ⱦ���ڵ��������� ���� 1920X1080X4���صĴ��ڵ���������Ϊ8294405��
	int Width; //���廭���Ŀ��
	int Height; //���廭���ĸ�
	//unsigned char colorbuffer[Width*Height*4];

};




