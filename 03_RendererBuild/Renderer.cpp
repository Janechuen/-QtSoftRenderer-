#include "Renderer.h"
#include <iostream>

#include <string>
#include <Core.h>

Renderer::Renderer(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::RendererClass)
{
	ui->setupUi(this);
	this->resize(1920, 1080);
	RenderWindow = nullptr;
	loop = new RenderRoute(width(), height(), nullptr);
	loopThread = new QThread(this);
	loop->moveToThread(loopThread);
	connect(loopThread, &QThread::started, loop, &RenderRoute::loop);
	connect(loopThread, &QThread::finished, loop, &RenderRoute::deleteLater);
	//第三个连接，就是将发射信号和接收信号链接在一起
	connect(loop, &RenderRoute::frameOut, this, &Renderer::receiveFrame);
	loopThread->start();
}
//析构函数 释放多线程 和渲染循环
Renderer::~Renderer()
{
	delete ui;
	loop->stopIt();
	loopThread->quit();
	loopThread->wait();
	if (RenderWindow)delete RenderWindow;
	if (loopThread)delete loopThread;
	loop = nullptr;
	RenderWindow = nullptr;
	loopThread = nullptr;
}
//QT窗口绘制函数 当receiveFrame接收到RenderRoute类送来的char数据填装新的纹理后使用update函数自动调用
void Renderer::paintEvent(QPaintEvent* event)
{
	if (RenderWindow)//判断指针是否为空
	{
		QPainter DrawFrame(this); //创建QT绘画组件
		DrawFrame.drawImage(QPoint(0, 0), *RenderWindow);//使用Drawimage函数 接收两个参数Qpoint二维 uchar 的指针类型数组
		//DrawFrame.end();
	}
	QWidget::paintEvent(event);
}
//接收 渲染循环渲染完毕的 帧缓冲 
void Renderer::receiveFrame(unsigned char* data)
{
	if (RenderWindow) delete RenderWindow;
	//给RenderWindow赋值Qimage data即
	RenderWindow = new QImage(data, width(), height(), QImage::Format_RGBA8888);
	//调用paintEvent函数将 FrameBuffer画到窗口上
	update();
}

#pragma region 注释代码
//bool _DrawTriangle::PixelinTriangle(vec2 p1, vec2 p2, vec2 p3, int x, int y)
//{
//	vec2 P = { x,y };
//	vec2 AB = p2 - p1; vec2 BC = p3 - p2; vec2 CA = p1 - p3;
//	printf("AB；%d",AB);
//	vec2 AP = P - p1; vec2 BP = P - p2; vec2 CP = P - p3;
//	int r1 = cross_2(AB, AP), r2 = cross_2(BC, BP), r3 = cross_2(CA, CP);
//	if (!r1 || !r2 || !r3) return true; // =0情况 就是 p点在三角形边缘上
//	if (r1 > 0 && r2 > 0 && r3 > 0)return true; //叉积特性 同方向视为在三角形范围内
//	if (r1 < 0 && r2 < 0 && r3 < 0)return true;
//	return false;
//}
//
//vec3 _DrawTriangle::PixelinTriangleColor(vec2 p1, vec2 p2, vec2 p3, int x, int y)
//{
//	vec2 P = { x,y };
//	vec2 v0 = p2 - p1, v1 = p3 - p1, v2 = P - p1;
//	float d00 = v0 * v0;
//	float d01 = v0 * v1;
//	float d11 = v1 * v1;
//	float d20 = v2 * v0;
//	float d21 = v2 * v1;
//	float denom = d00 * d11 - d01 * d01;
//	float r1 = (d11 * d20 - d01 * d21) / denom;
//	float r2 = (d00 * d21 - d01 * d20) / denom;
//	float r3 = 1 - r1 - r2;
//
//
//	//vec2 AB = p2 - p1; vec2 BC = p3 - p2; vec2 CA = p1 - p3;
//	//vec2 AP = P - p1; vec2 BP = P - p2; vec2 CP = P - p3;
//	//AB=AB.normalized(), BC=BC.normalized(), CA=CA.normalized();
//	//AP=AP.normalized(), BP=BP.normalized(), CP=CP.normalized();
//	//double r1 = cross_2(AB, AP), r2 = cross_2(BC, BP), r3 = cross_2(CA, CP);
//	/*double r1 = cross_2(AP, AB), r2 = cross_2(BP, BC), r3 = cross_2(CP,CA);*/
//	vec3 r = { 255,0,0 }, g = { 0,255,0 }, b = { 0,0,255 };
//	vec3 outcol = {0,0,0};
//	outcol.x = std::abs(r1 * r.x + r2 * g.x + r3 * b.x);
//	outcol.y = std::abs(r1 * r.y + r2 * g.y + r3 * b.y);
//	outcol.z = std::abs(r1 * r.z + r2 * g.z + r3 * b.z);
//	return outcol;
//}
//
//void _DrawPixel(QPainter &p, vec2 pos)
//{
//	p.drawPoint(QPoint(pos.x,pos.y));
//}
//#pragma region 划线版本
//void _DrawTriangle::paintEvent(QPaintEvent* event)
//{
//	//QPainter painter(this);
//	//QPen pen(QColor(255, 0, 0));
//	//pen.setWidth(2);
//	//pen.setStyle(Qt::SolidLine);
//	//painter.setPen(pen);
//	int tempnum = 0;
//	vec2 tempvec;
//
//	//画线
//	/*for (int i = 0; i < points.size() - 1; i++)
//	{
//		painter.drawLine(QPoint(points[i][0], points[i][1]), QPoint(points[i + 1][0], points[i + 1][1]));
//	}
//	painter.drawLine(QPoint(points[2][0], points[2][1]), QPoint(points[0][0], points[0][1]));*/
//	
//	
//	//寻找三角形边框的最小范围
//	int minx=0, miny=0, maxx=0, maxy=0, tempx=0,tempy=0;
//	minx = std::min((int)points[0][0], std::min((int)points[1][0], (int)points[2][0]));
//	miny = std::min((int)points[0][1], std::min((int)points[1][1], (int)points[2][1]));
//	maxx = std::max((int)points[0][0], std::max((int)points[1][0], (int)points[2][0]));
//	maxy = std::max((int)points[0][1], std::max((int)points[1][1], (int)points[2][1]));
//	//遍历正方形边框 判断像素是否在三角形内 如果是 则绘制像素颜色 没有则不绘制
//	for (int i=minx ; i < maxx; ++i)
//	{
//		for (int j = miny; j < maxy; ++j)
//		{	
//			if (PixelinTriangle(points[0], points[1], points[2], i, j))
//			{
//				vec2 pos = { i,j };
//				QPainter painter(this);
//				vec3 col = PixelinTriangleColor(points[0], points[1], points[2], i, j);
//				QPen pen(QColor(col.x, col.y, col.z));
//				pen.setWidth(2);
//				pen.setStyle(Qt::SolidLine);
//				painter.setPen(pen);
//
//				//pen.setColor();
//				painter.drawPoint(QPoint(pos.x,pos.y));
//			}
//		}
//	}
//
//}
//#pragma endregion

#pragma endregion

