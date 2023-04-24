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
	vec4 v1{ 0, 0, 0,0 }, v2{ 1920, 1080, 0,0 }, v3{ 500, 700, 0 ,0 }; //画线测试
	Mesh* msh = new Mesh;
	msh->triangle(v1, v2, v3);
	pipeline->setVertexBuffer(msh->vertices);
	pipeline->setIndexBuffer(msh->index);
	while (!stopped)
	{
		//渲染循环While内将上一帧绘制好的图像清空为默认颜色 这里填充为黑色
		pipeline->clearBuffer(vec4{0, 0, 0, 1.0f});
		//渲染循环While内核心函数：负责绘制图像
		pipeline->drawIndex(Pipeline::Fill2D);
		//双缓冲交换 因为DrawIndex绘制的是back 
		pipeline->swapBuffer();
		emit RenderRoute::frameOut(pipeline->output());
	}
}