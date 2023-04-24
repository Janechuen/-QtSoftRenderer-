#include "Pipeline.h"
#include "algorithm"
using namespace std;

Pipeline::~Pipeline()
{
    if (m_shader)delete m_shader;
    if (m_frontBuffer)delete m_frontBuffer;
    if (m_backBuffer)delete m_backBuffer;
    m_shader = nullptr;
    m_frontBuffer = nullptr;
    m_backBuffer = nullptr;
}

void Pipeline::initialize()
{
    if (m_frontBuffer != nullptr)delete m_frontBuffer;
    if (m_backBuffer)delete m_backBuffer;
    if (m_shader)delete m_shader;
    m_frontBuffer = new FrameBuffer(width, height);
    m_backBuffer = new FrameBuffer(width, height);
    m_shader = new SimpleShader(); //后续添加 默认类型shader
}

void Pipeline::drawIndex(RenderMode mode)
{
	//
	// 开始判断渲染模式
	// 
    //如果序列为空 不执行绘制操作
    if (m_indices.empty())return;
	if (mode==Wire2D)
	{
		Vertex v1 = m_vertices[0];
		Vertex v2 = m_vertices[1];
		Vertex v3 = m_vertices[2];
		bresenham2d(v1.Position,v2.Position);
	}
	if (mode==Fill2D)
	{
		Vertex v1 = m_vertices[0];
		Vertex v2 = m_vertices[1];
		Vertex v3 = m_vertices[2];
		Rasterization2d(v1.Position, v2.Position, v3.Position);
	}
	if (mode==Wire2D)
	{

	}
	if (mode==Wire3D)
	{

	}
	else
	{
		qDebug() << "错误：PipeLine.Drawindwx 渲染模式RenderMode为空 检查这两个和渲染循环中的调用";
		return;
	}
}

void Pipeline::clearBuffer(const vec4& color, bool depth)
{
    (void)depth;
        m_backBuffer->InitFrameBuffer(color);
}

void Pipeline::setShaderMode(ShadingMode mode)
{
    if (m_shader)delete m_shader;
    if (mode == Simple)
       m_shader = new SimpleShader();//后续添加 默认类型shader
    else if(mode==Phong);
}

void Pipeline::swapBuffer()
{
    FrameBuffer* tmp = m_frontBuffer;
    m_frontBuffer = m_backBuffer;
    m_backBuffer = tmp;
}

#pragma region 2D光栅化
//2D 线框光栅化模式
void Pipeline::bresenham2d(vec4 from, vec4 to)
{
	/*int dx = tx - fx, dy = ty - fy;
	int sx = 1, sy = 1;
	int nowX = fx, nowY = fy;
	if (dx < 0) {
		sx = -1;
		dx = -dx;
	}
	if (dy < 0) {
		sy = -1;
		dy = -dy;
	}
*/

	int tx = to.x;
	int ty = to.y;
	int fx = from.x;
	int fy = from.y;
	int x1, x2, y1, y2;
	x1 = fx;
	y1 = fy;
	x2 = tx;
	y2 = ty;
	int dx = abs((x2 - x1));
	int dy = abs(y2 - y1);
	int dx2 = (2 * dx);
	int dy2 = (2 * dy);
	int e = (-1 * dx);
	if (dy < dx)
	{
		for (int i = x1; i < x2; i++)
		{
			//painter.drawPoint(QPoint(i, y1));
			m_backBuffer->UpdataFrameBuffer(i, y1, vec4{ 1,0,0,1 });
			e = e + dy2;
			if (e < 0)//<0.5不满足向上像素绘制的需求
			{
				printf("绘制顶点序号:%d x:%d y:%d \r\n", i, i, y1);
			}
			else//满足绘制需求
			{
				m_backBuffer->UpdataFrameBuffer(i, y1, vec4{ 1,0,0,1 });
				printf("绘制顶点序号:%d x:%d y:%d \r\n", i, i, y1);
				y1 = y1 + 1;
				e = e - dx2;
			}
		}
	}



	/*vec4 tmp;
	if (dy <= dx)
	{
		int d = 2 * dy - dx;
		for (int i = 0; i <= dx; ++i)
		{
			tmp = lerp(from, to, static_cast<double>(i) / dx);
			m_backBuffer->UpdataFrameBuffer(nowX, nowY, m_shader->fragmentShader(tmp));
			nowX += sx;
			if (d <= 0)d += 2 * dy;
			else {
				nowY += sy;
				d += 2 * dy - 2 * dx;
			}
		}
	}
	else
	{
		int d = 2 * dx - dy;
		for (int i = 0; i <= dy; ++i)
		{
			tmp = lerp(from, to, static_cast<double>(i) / dy);
			m_backBuffer->UpdataFrameBuffer(nowX, nowY, m_shader->fragmentShader(tmp));
			nowY += sy;
			if (d < 0)d += 2 * dx;
			else {
				nowX += sx;
				d -= 2 * dy - 2 * dx;
			}
		}
	}*/
}
//2D 光栅化填充遍历

bool Pipeline::barycentric(vec2 p1, vec2 p2, vec2 p3, int x, int y)
{
	vec2 P = { x,y };
	vec2 AB = p2 - p1; vec2 BC = p3 - p2; vec2 CA = p1 - p3;
	printf("AB；%d", AB);
	vec2 AP = P - p1; vec2 BP = P - p2; vec2 CP = P - p3;
	int r1 = cross_2(AB, AP), r2 = cross_2(BC, BP), r3 = cross_2(CA, CP);
	if (!r1 || !r2 || !r3) return true; // =0情况 就是 p点在三角形边缘上
	if (r1 > 0 && r2 > 0 && r3 > 0)return true; //叉积特性 同方向视为在三角形范围内
	if (r1 < 0 && r2 < 0 && r3 < 0)return true;
	return false;
}

void Pipeline::Rasterization2d(vec4 v1,vec4 v2,vec4 v3)
{
	//寻找三角形边框的最小范围
	int minx = 0, miny = 0, maxx = 0, maxy = 0, tempx = 0, tempy = 0;
	minx = std::min((int)v1.x, std::min((int)v2.x, (int)v3.x));
	miny = std::min((int)v1.y, std::min((int)v2.y, (int)v3.y));
	maxx = std::max((int)v1.x, std::max((int)v2.x, (int)v3.x));
	maxy = std::max((int)v1.y, std::max((int)v2.y, (int)v3.y));
	//遍历正方形边框 判断像素是否在三角形内 如果是 则绘制像素颜色 没有则不绘制
	for (int i = minx; i < maxx; ++i)
	{
		for (int j = miny; j < maxy; ++j)
		{
			if (barycentric(vec2{ v1.x,v1.y }, vec2{ v2.x,v2.y }, vec2{ v3.x,v3.y }, i, j))
			{
				vec2 pos = { i,j };
				vec3 col = PixelinTriangleColor2d(vec2{ v1.x,v1.y }, vec2{ v2.x,v2.y }, vec2{ v3.x,v3.y }, i, j);
				m_backBuffer->UpdataFrameBuffer(pos.x, pos.y, vec4{col.x,col.y,col.z,1});
			}
		}
	}
}

vec3 Pipeline::PixelinTriangleColor2d(vec2 p1, vec2 p2, vec2 p3, int x, int y)
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
	vec3 r = { 1,0,0 }, g = { 0,1,0 }, b = { 0,0,1 };
	vec3 outcol = { 0,0,0 };
	outcol.x = std::abs(r1 * r.x + r2 * g.x + r3 * b.x);
	outcol.y = std::abs(r1 * r.y + r2 * g.y + r3 * b.y);
	outcol.z = std::abs(r1 * r.z + r2 * g.z + r3 * b.z);
	return outcol;
}


#pragma endregion

