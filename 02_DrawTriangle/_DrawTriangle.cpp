#include "_DrawTriangle.h"
#include <iostream>


_DrawTriangle::_DrawTriangle(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	this->setWindowTitle("LightningHawk<SoftEngine>");//修改窗口命名
	this->setWindowIcon(QIcon("A:/PROJECT_WORKS/PYTHON_PROJECT/TextureBlendTool/Icon"));//修改窗口ICON
	this->resize(1920, 1080);
}

bool _DrawTriangle::PixelinTriangle(vec2 p1, vec2 p2, vec2 p3, int x, int y)
{
	vec2 P = { x,y };
	vec2 AB = p2 - p1; vec2 BC = p3 - p2; vec2 CA = p1 - p3;
	vec2 AP = P - p1; vec2 BP = P - p2; vec2 CP = P - p3;
	int r1 = cross_2(AB, AP), r2 = cross_2(BC, BP), r3 = cross_2(CA, CP);
	if (!r1 || !r2 || !r3) return true; // =0情况 就是 p点在三角形边缘上
	if (r1 > 0 && r2 > 0 && r3 > 0)return true; //叉积特性 同方向视为在三角形范围内
	if (r1 < 0 && r2 < 0 && r3 < 0)return true;
	return false;
}

vec3 _DrawTriangle::PixelinTriangleColor(vec2 p1, vec2 p2, vec2 p3, int x, int y)
{
	vec2 P = { x,y };
	vec2 v0 = p2 - p1, v1 = p3 - p1, v2 = P - p1;
	float d00 = v0 * v0;
	float d01 = v0 * v1;
	float d11 = v1 * v1;
	float d20 = v2 * v0;
	float d21 = v2 * v1;
	float denom = d00 * d11 - d01 * d01;
	float r1 = (d11 * d20 - d01 * d21) / denom;
	float r2 = (d00 * d21 - d01 * d20) / denom;
	float r3 = 1 - r1 - r2;
	vec3 r = { 255,0,0 }, g = { 0,255,0 }, b = { 0,0,255 };
	vec3 outcol = {0,0,0};
	outcol.x = std::abs(r1 * r.x + r2 * g.x + r3 * b.x);
	outcol.y = std::abs(r1 * r.y + r2 * g.y + r3 * b.y);
	outcol.z = std::abs(r1 * r.z + r2 * g.z + r3 * b.z);
	return outcol;
}


#pragma region 划线版本
void _DrawTriangle::paintEvent(QPaintEvent* event)
{
	std::vector<vec2>points{};
	std::vector<vec2> t;
	t.push_back(vec2{ 0,0 });
	t.push_back(vec2{ 0,1080 });
	t.push_back(vec2{ 1920,500});
	points = t;
	//寻找三角形边框的最小范围
	int minx=0, miny=0, maxx=0, maxy=0, tempx=0,tempy=0;
	minx = std::min((int)points[0][0], std::min((int)points[1][0], (int)points[2][0]));
	miny = std::min((int)points[0][1], std::min((int)points[1][1], (int)points[2][1]));
	maxx = std::max((int)points[0][0], std::max((int)points[1][0], (int)points[2][0]));
	maxy = std::max((int)points[0][1], std::max((int)points[1][1], (int)points[2][1]));
	//遍历正方形边框 判断像素是否在三角形内 如果是 则绘制像素颜色 没有则不绘制
	QPainter painter(this);
	for (int i=minx ; i < maxx; ++i)
	{
		for (int j = miny; j < maxy; ++j)
		{	
			if (PixelinTriangle(points[0], points[1], points[2], i, j))
			{
				vec2 pos = { i,j };
				vec3 col = PixelinTriangleColor(points[0], points[1], points[2], i, j);
				QPen pen(QColor(col.x, col.y, col.z));
				//QPen pen(QColor(255, 0, 0));
				pen.setWidth(2);
				pen.setStyle(Qt::SolidLine);
				painter.setPen(pen);
				painter.drawPoint(QPoint(pos.x,pos.y));
			}
		}
	}

}
#pragma endregion
