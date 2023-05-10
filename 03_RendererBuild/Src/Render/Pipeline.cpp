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
	m_DepthBuffer = nullptr;
}

void Pipeline::initialize()
{
    if (m_frontBuffer != nullptr)delete m_frontBuffer;
    if (m_backBuffer)delete m_backBuffer;
    //if (m_shader)delete m_shader;
    m_frontBuffer = new FrameBuffer(width, height);
    m_backBuffer = new FrameBuffer(width, height);
	m_DepthBuffer = new FrameBuffer(width,height);
    //m_shader = new  SimpleShader(); //后续添加 默认类型shader
}

V2F Pipeline::VS(Appdata a)
{
	//遍历顶点 将顶点从本地空间变换到 世界 相机 投影 最后到裁剪空间 屏幕空间
	V2F VS_Output;
	
	//mat<4, 4>ViewMatrix = GetViewMatrix({ 0,0,-10 }, { 0,0,0 }, { 0,1,0 });
	double near = 0.3;
	double far = 50;
	mat<4, 4>ProjectionMatrix = GetProjectionMatrix((double)width / (double)height, 90 * 3.14 / 180.f, near, far);
	//顶点着色器循环 会对每个顶点进行基础的MVP处理
	for (int i = 0; i < a.POSITION.size(); i++)
	{
		//MVP变换
		mat<4, 4>TransformMatrix = GetTransformMatrix();
		vec4 VSOutput_Pos = vec4{ a.POSITION[i].x,a.POSITION[i].y,a.POSITION[i].z,1.0 };
		VSOutput_Pos = TransformMatrix * VSOutput_Pos;//M变换 从模型空间进入世界空间
		mat<4, 4>ViewMatrix = GetViewMatrix({ 0,0,-10 }, { VSOutput_Pos.x,VSOutput_Pos.y,VSOutput_Pos.z }, { 0,1,0 });
		VSOutput_Pos = ViewMatrix * VSOutput_Pos; //V变换 从世界空间进入视口空间
		VS_Output.view_position.push_back(VSOutput_Pos);
		VSOutput_Pos = ProjectionMatrix * VSOutput_Pos; //P变换 从视口空间进入视锥裁剪空间
		VS_Output.position.push_back(VSOutput_Pos);
		vec4 Cs_Pos = VSOutput_Pos;
		Cs_Pos = vec4{ Cs_Pos.x / Cs_Pos.w, Cs_Pos.y / Cs_Pos.w, Cs_Pos.z, Cs_Pos.w };//Perspectivedivide透视除法 xyz/w 进入NDC空间
		Cs_Pos = vec4{ (width * Cs_Pos.x / 2) + width / 2,(height * Cs_Pos.y / 2) + height / 2 ,Cs_Pos.z,Cs_Pos.w };//viewportmapping视口片换
		VS_Output.screen_position.push_back(Cs_Pos);
	}
	return VS_Output;
}

void Pipeline::FS_Wire(V2F in, Appdata a)
{
	for (int i = 0; i < a.P_INDEX.size(); i += 3)//获取模型位置序列
	{
		std::vector<vec4> aa = in.screen_position;//检测输出顶点
		vec4 pointa = in.screen_position[a.P_INDEX[i]];
		vec4 pointb = in.screen_position[a.P_INDEX[i+1]];
		vec4 pointc = in.screen_position[a.P_INDEX[i+2]];
		bresenham2d(pointa, pointb);
		bresenham2d(pointb, pointc);
		bresenham2d(pointc, pointa);
	}
}

void Pipeline::FS_Fill(V2F in, Appdata a)
{
	for (int i = 0; i < a.P_INDEX.size(); i += 3)//获取模型位置序列
	{
		
		std::vector<vec4> aa = in.screen_position;//检测输出顶点
		vec4 pointa = vec4{ in.screen_position[a.P_INDEX[i]] };
		vec4 pointb = vec4{ in.screen_position[a.P_INDEX[i + 1]] };
		vec4 pointc = vec4{ in.screen_position[a.P_INDEX[i + 2]] };
		//背面剔除 检查三角面是否是反的 如果是那么不参与大奥光栅化和fragment中
		if (BackfaceCulling(pointa, pointb, pointc))
		{
			Rasterization2d(pointa, pointb, pointc, false);
		}
		//Fragment Shader

		//Depth Test
		 
	}
}

void Pipeline::FS_Depth(V2F in, Appdata a)
{
	for (int i = 0; i < a.P_INDEX.size(); i += 3)//获取模型位置序列
	{

		std::vector<vec4> aa = in.screen_position;//检测输出顶点
		vec4 pointa = in.screen_position[a.P_INDEX[i]];
		vec4 pointb = in.screen_position[a.P_INDEX[i + 1]];
		vec4 pointc = in.screen_position[a.P_INDEX[i + 2]];
		//背面剔除 检查三角面是否是反的 如果是那么不参与大奥光栅化和fragment中
		if (BackfaceCulling(pointa, pointb, pointc))
		{
			Rasterization2d(pointa, pointb, pointc, true);
		}
		//Fragment Shader
		//Depth Test
	}
}

bool Pipeline::BackfaceCulling(vec4 v1, vec4 v2, vec4 v3)
{
		vec2 p1 = vec2{ v1.x,v1.y };
		vec2 p2 = vec2{ v2.x,v2.y };
		vec2 p3 = vec2{ v3.x,v3.y };
		vec2 AB = p2 - p1; vec2 BC = p3 - p2; vec2 CA = p1 - p3;
		int r1 = cross_2(AB, BC), r2 = cross_2(BC, CA), r3 = cross_2(CA, AB);
		if (r1 > 0 && r2 > 0 && r3 > 1)return false; //叉积特性 同方向视为在三角形范围内
		if (r1 < 0 & r2 < 0 && r3 < 0)return true;
}

void Pipeline::drawIndex(RenderMode mode, Appdata a)
{
    //如果序列为空 不执行绘制操作
	if (a.P_INDEX.empty())return;
	if (mode==Wire2D)
	{
	//	Vertex v1 = m_vertices[0];
	//	Vertex v2 = m_vertices[1];
	//	Vertex v3 = m_vertices[2];
	//	bresenham2d(v1.Position,v2.Position);
	}
	if (mode==Fill2D)
	{
	//	Vertex v1 = m_vertices[0];
	//	Vertex v2 = m_vertices[1];
	//	Vertex v3 = m_vertices[2];
	//	Rasterization2d(v1.Position, v2.Position, v3.Position);
	}
	if (mode==Wire3D)
	{
		V2F vs = VS(a);//【顶点着色器】【VERTEX SHADER】
		FS_Wire(vs,a);//【像素着色器】【FRAGMENT SHADER】
	}
	if (mode==Fill3D)
	{
		V2F vs = VS(a);//【顶点着色器】【VERTEX SHADER】
		FS_Fill(vs, a);//【像素着色器】【FRAGMENT SHADER】
	}
	if (mode==DEPTH3D)
	{
		V2F vs = VS(a);	//【顶点着色器】【VERTEX SHADER】
		FS_Depth(vs, a);//【像素着色器】【FRAGMENT SHADER】
	}
	else
	{
		qDebug() << "错误：PipeLine.Drawindwx 渲染模式RenderMode为空 检查这两个和渲染循环中的调用";
		return;
	}
}

void Pipeline::clearBuffer(const vec4& color)
{
    //(void)depth;
	m_backBuffer->InitFrameBuffer(color); //重置Color Buffer
	m_DepthBuffer->InitDepthBuffer(0);//重置Depth Buffer
}

void Pipeline::setShaderMode(ShadingMode mode)
{
    if (m_shader)delete m_shader;
    //if (mode == Simple)
      // m_shader = new SimpleShader();//后续添加 默认类型shader
	//else if(mode==Phong);
}

void Pipeline::swapBuffer()//交换buffer
{
    FrameBuffer* tmp = m_frontBuffer;
    m_frontBuffer = m_backBuffer;
    m_backBuffer = tmp;
}

#pragma region 光栅化
//函数说明：
//2D 两点画直线
void Pipeline::bresenham2d(vec4 from, vec4 to)
{
	int dx = to.x - from.x, dy = to.y - from.y;
	int sx = 1, sy = 1;
	int nowX = from.x, nowY = from.y;
	if (dx < 0) {
		sx = -1;
		dx = -dx;
	}
	if (dy < 0) {
		sy = -1;
		dy = -dy;
	}

	if (dy <= dx)
	{
		int d = 2 * dy - dx;
		for (int i = 0; i <= dx; ++i)
		{
			m_backBuffer->UpdataFrameBuffer(nowX, nowY, vec4{ 1,0,0,1 });
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
			m_backBuffer->UpdataFrameBuffer(nowX, nowY, vec4{ 1,0,0,1 });
			nowY += sy;
			if (d < 0)d += 2 * dx;
			else {
				nowX += sx;
				d -= 2 * dy - 2 * dx;
			}
		}
	}
	
}
//2D 【光栅化】判断片元是否在三角形范围内
bool Pipeline::barycentric(vec2 p1, vec2 p2, vec2 p3, int x, int y)
{
	//叉积判断法
	vec2 P = { x,y };
	vec2 AB = p2 - p1; vec2 BC = p3 - p2; vec2 CA = p1 - p3;
	vec2 AP = P - p1; vec2 BP = P - p2; vec2 CP = P - p3;
	double r1 = cross_2(AB, AP), r2 = cross_2(BC, BP), r3 = cross_2(CA, CP);
	if (!r1 || !r2 || !r3) return true; // =0情况 就是 p点在三角形边缘上
	if (r1 > 0 && r2 > 0 && r3 > 0)return true; //叉积特性 同方向视为在三角形范围内
	if (r1 < 0 & r2 < 0 && r3 < 0)return true;//这里改为-0,1而不是0的原因是为了避免三角形边界因为精度问题而将像素舍弃出现黑点问题 为了解决问题 修改像素剔除范围
	return false;
}

vec3 Pipeline::barycentricTriangle(vec2 p1, vec2 p2, vec2 p3, int x, int y)
{
	//三角重心坐标
	double Z = ((p1.y - p2.y) * x + (p2.x - p1.x) * y + p1.x * p2.y - p2.x * p1.y) / ((p1.y - p2.y) * p3.x + (p2.x - p1.x) * p3.y + p1.x * p2.y - p2.x * p1.y);
	double Y = ((p1.y - p3.y) * x + (p3.x - p1.x) * y + p1.x * p3.y - p3.x * p1.y) / ((p1.y - p3.y) * p2.x + (p3.x - p1.x) * p2.y + p1.x * p3.y - p3.x * p1.y);
	double X = 1 - Z - Y;
	return vec3{ X,Y,Z };
}

void Pipeline::Rasterization2d(vec4 v1,vec4 v2,vec4 v3, bool DepthMode)
{
	int bondscale = 1;//寻找三角形边框的最小范围 bondscale 放大边框 解决有的时候垂直线段即是边界导致边线被剔除导致渲染错误的情况出现
	int minx = 0, miny = 0, maxx = 0, maxy = 0, tempx = 0, tempy = 0;
	minx = std::min((int)v1.x - bondscale, std::min((int)v2.x- bondscale, (int)v3.x- bondscale));
	miny = std::min((int)v1.y - bondscale, std::min((int)v2.y- bondscale, (int)v3.y- bondscale));
	maxx = std::max((int)v1.x + bondscale, std::max((int)v2.x+ bondscale, (int)v3.x+ bondscale));
	maxy = std::max((int)v1.y + bondscale, std::max((int)v2.y+ bondscale, (int)v3.y+ bondscale));
	//遍历正方形边框 判断像素是否在三角形内 如果是 则绘制像素颜色 没有则不绘制
	double Zdistance = 20;
	for (int i = minx; i < maxx; ++i)
	{
		for (int j = miny; j < maxy; ++j)
		{
			if (barycentric(vec2{ v1.x,v1.y }, vec2{ v2.x,v2.y }, vec2{ v3.x,v3.y }, i, j))
			{
				vec2 pos = { i,j };
				vec3 barycentricz = barycentricTriangle(vec2{ v1.x,v1.y }, vec2{ v2.x,v2.y }, vec2{ v3.x,v3.y }, i, j);
				double z = abs(1-(-v1.z/ Zdistance)) * barycentricz.x + abs(1 - (-v2.z / Zdistance)) * barycentricz.y + abs(1 - (-v3.z / Zdistance)) * barycentricz.z;//三角重心重心插值深度
				if (barycentricz.x > 0|| barycentricz.y > 0|| barycentricz.z > 0)
				{
					if (z > m_DepthBuffer->GetDepthBuffer(i, j))//深度测试 将当前像素的z值和Zbuffer的z值比较
					{
						m_DepthBuffer->UpdataDepthBuffer(pos.x, pos.y, z);//更新深度缓存
						if (DepthMode==true)
						{
							m_backBuffer->UpdataFrameBuffer(pos.x, pos.y, vec4{ z,z,z ,1 });//绘制深度信息
						}
					} 
				}
				
				if (DepthMode==false)
				{
					m_backBuffer->UpdataFrameBuffer(pos.x, pos.y, vec4{ 0.3,0.4,0.2,1 });
					//m_backBuffer->UpdataFrameBuffer(pos.x, pos.y, vec4{ col.x,col.y,col.z,1 });//更新颜色缓存	
				}
				//vec4 FragmentShader();//【像素着色器】 
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


