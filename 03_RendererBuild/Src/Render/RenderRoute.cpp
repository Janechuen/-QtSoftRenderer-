#include "RenderRoute.h"

RenderRoute::RenderRoute(int w, int h, QObject* parent)
	: QObject(parent), width(w), height(h), channel(4)
{
	stopped = false;
	pipeline = new Pipeline(width, height);
}

void RenderRoute::stopIt() {
	stopped = true;
}

void RenderRoute::loop()
{
	pipeline->initialize();
	//vec4 v1{ 100, 100, 0,0 }, v2{ 1200, 200, 0,0 }, v3{ 500, 700, 0 ,0};
	vec4 v1{ 0, 0, 0,0 }, v2{ 1920, 1080, 0,0 }, v3{ 500, 700, 0 ,0 }; //���߲���
	Mesh* msh = new Mesh;
	msh->triangle(v1, v2, v3);
	pipeline->setVertexBuffer(msh->vertices);
	pipeline->setIndexBuffer(msh->index);
	while (!stopped)
	{
		//��Ⱦѭ��While�ڽ���һ֡���ƺõ�ͼ�����ΪĬ����ɫ �������Ϊ��ɫ
		pipeline->clearBuffer(vec4{0, 0, 0, 1.0f});
		//��Ⱦѭ��While�ں��ĺ������������ͼ��
		pipeline->drawIndex(Pipeline::Fill2D);
		//˫���彻�� ��ΪDrawIndex���Ƶ���back 
		pipeline->swapBuffer();
		emit RenderRoute::frameOut(pipeline->output());
	}
}