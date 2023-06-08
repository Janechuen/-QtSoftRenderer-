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
	VS_Output.uv = a.TEXCOORD0;
	VS_Output.uv_index = a.UV_INDEX;
	vec4 VSOutput_Pos;
	vec4 VSOutput_Nor ;
	//顶点着色器循环 会对每个顶点进行基础的MVP处理
	for (int i = 0; i < a.POSITION.size(); i++)
	{
		//【模型坐标 Position】
		//M变换  【模型——>世界】 
		mat<4, 4>TransformMatrix = GetTransformMatrix();
		VSOutput_Pos = vec4{ a.POSITION[i].x,a.POSITION[i].y,a.POSITION[i].z,1.0 };
		VSOutput_Pos = TransformMatrix * VSOutput_Pos;//M变换 从模型空间进入世界空间
		vec4 worldposition = VSOutput_Pos;
		worldposition.w = 0;
		VS_Output.world_position.push_back(worldposition);//传给V2F在片元着色器中使用
		//V变换  【世界——>相机】 
		mat<4, 4>ViewMatrix = GetViewMatrix(m_cameraposition, { VSOutput_Pos.x,VSOutput_Pos.y,VSOutput_Pos.z }, { 0,1,0 });
		VSOutput_Pos = ViewMatrix * VSOutput_Pos; //V变换 从世界空间进入视口空间
		VS_Output.view_position.push_back(VSOutput_Pos);//传给V2F在片元着色器中使用
		//P变换  【相机——>裁剪】 
		mat<4, 4>ProjectionMatrix = GetProjectionMatrix((double)width / (double)height, m_fov, m_cameranear, m_camerafar);
		VSOutput_Pos = ProjectionMatrix * VSOutput_Pos; //P变换 从视口空间进入视锥裁剪空间
		VS_Output.position.push_back(VSOutput_Pos);//传给V2F在片元着色器中使用
		vec4 Cs_Pos = VSOutput_Pos;
		//透视除法  【裁剪——>NDC】
		Cs_Pos = vec4{ Cs_Pos.x / Cs_Pos.w, Cs_Pos.y / Cs_Pos.w, Cs_Pos.z, Cs_Pos.w };//Perspectivedivide透视除法 xyz/w 进入NDC空间
		//视口变换  【NDC——>屏幕】
		Cs_Pos = vec4{ (width * Cs_Pos.x / 2) + width / 2,(height * Cs_Pos.y / 2) + height / 2 ,Cs_Pos.z,Cs_Pos.w };//viewportmapping视口片换
		VS_Output.screen_position.push_back(Cs_Pos);//传给V2F在片元着色器中使用
	}
	for (int i = 0; i < a.NORMAL.size(); i++)//分开是因为顶点和法线数据量不一样
	{
		mat<4, 4>TransformMatrix = GetTransformMatrix();
		//【法线 Normal】
		VSOutput_Nor = vec4{a.NORMAL[i].x,a.NORMAL[i].y,a.NORMAL[i].z,0.0};//本地空间顶点法线
		//VSOutput_Nor = TransformMatrix.invert().transpose() * VSOutput_Nor;//世界空间顶点法线变换 这里的矩阵是逆转置矩阵 防止出现缩放导致法线不准确的问题
		VSOutput_Nor = TransformMatrix * VSOutput_Nor;
		VSOutput_Nor = VSOutput_Nor.normalized();

		//这步操作只是通过屏幕检查数值是否正确
		//VSOutput_Nor.x = VSOutput_Nor.x * 100;
		//VSOutput_Nor.y = VSOutput_Nor.y * 100;
		//VSOutput_Nor.z = VSOutput_Nor.z * 100;
		//mat<4, 4>ViewMatrix = GetViewMatrix(m_cameraposition, {0,0,1 }, { 0,1,0 });
		//VSOutput_Nor = ViewMatrix * VSOutput_Nor;
		//VSOutput_Nor = VSOutput_Nor.normalized();
		VS_Output.world_normal.push_back(VSOutput_Nor);//添加法线
	}
	return VS_Output;
}

void Pipeline::FS_Wire(V2F in, Appdata a)
{
	for (int i = 0; i < a.P_INDEX.size(); i += 3)//获取模型位置序列
	{
		vec4 pointa = in.screen_position[a.P_INDEX[i]];
		vec4 pointb = in.screen_position[a.P_INDEX[i+1]];
		vec4 pointc = in.screen_position[a.P_INDEX[i+2]];
		bresenham2d(pointa, pointb);
		bresenham2d(pointb, pointc);
		bresenham2d(pointc, pointa);
	}
}

void Pipeline::FS_Fill(V2F in, Appdata a)
{	//整理三角形在片元阶段中所需要用到片元数据 
	for (int i = 0; i < a.P_INDEX.size(); i += 3)//获取模型位置序列
	{
		vec4 pointa = vec4{ in.screen_position[a.P_INDEX[i]] };
		vec4 pointb = vec4{ in.screen_position[a.P_INDEX[i + 1]] };
		vec4 pointc = vec4{ in.screen_position[a.P_INDEX[i + 2]] };
		vec4 worldposa = vec4{ in.world_position[a.P_INDEX[i]] };
		vec4 worldposb = vec4{ in.world_position[a.P_INDEX[i+1]] };
		vec4 worldposc = vec4{ in.world_position[a.P_INDEX[i+2]] };
		vec2 uva = vec2{ in.uv[a.UV_INDEX[i]]};
		vec2 uvb = vec2{ in.uv[a.UV_INDEX[i+1]] };
		vec2 uvc = vec2{ in.uv[a.UV_INDEX[i+2]] };
		vec4 normmala = vec4{ in.world_normal[a.N_INDEX[i]] };
		vec4 normmalb = vec4{ in.world_normal[a.N_INDEX[i+1]] };
		vec4 normmalc = vec4{ in.world_normal[a.N_INDEX[i+2]] };
	
		vec4 t = C_ComputerT(worldposa, worldposb, worldposc, uva, uvb, uvc);//计算平面切线
		//将切线正交化
		vec4 tangenta = t - normmala * (t * normmala);
		tangenta = tangenta.normalized();
		vec4 tangentb = t - normmalb * (t * normmalb);
		tangentb = tangentb.normalized();
		vec4 tangentc = t - normmalc * (t * normmalc);
		tangentc = tangentc.normalized();
		//将法线和切线重新组合新正交坐标系
		vec4 bitangenta = cross_4(normmala, tangenta);
		vec4 bitangentb = cross_4(normmalb, tangentb);
		vec4 bitangentc = cross_4(normmalc, tangentc);
		
		//背面剔除 检查三角面是否是反的 如果是那么不参与大奥光栅化和fragment中
		if (BackfaceCulling(pointa, pointb, pointc))
		{
			//Rasterization2d(pointa, pointb, pointc,uva,uvb,uvc,in, false);
			Rasterization3dFill(pointa, pointb, pointc, uva, uvb, uvc, normmala, normmalb, normmalc, worldposa, worldposb, worldposc, tangenta, tangentb, tangentc, bitangenta, bitangentb, bitangentc,in, false);
		}
	}
}

void Pipeline::FS_Depth(V2F in, Appdata a)
{
	for (int i = 0; i < a.P_INDEX.size(); i += 3)//获取模型位置序列
	{
		vec4 pointa = in.screen_position[a.P_INDEX[i]];
		vec4 pointb = in.screen_position[a.P_INDEX[i + 1]];
		vec4 pointc = in.screen_position[a.P_INDEX[i + 2]];
		vec2 uva = in.uv[a.UV_INDEX[i]];
		vec2 uvb = in.uv[a.UV_INDEX[i+1]];
		vec2 uvc = in.uv[a.UV_INDEX[i+2]];
		//背面剔除 检查三角面是否是反的 如果是那么不参与大奥光栅化和fragment中
		if (BackfaceCulling(pointa, pointb, pointc))
		{
			Rasterization2d(pointa, pointb, pointc, uva, uvb, uvc, in, true);
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
		if (r1 > 0 && r2 > 0 && r3 > 0)return false; //叉积特性 同方向视为在三角形范围内
		if (r1 < 0 & r2 < 0 && r3 < 0)return true;
}

void Pipeline::drawIndex(RenderMode mode)
{

    //如果序列为空 不执行绘制操作
	//if (a.P_INDEX.empty())return;
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
		v2f = VS(appdata);//【顶点着色器】【VERTEX SHADER】
		FS_Wire(v2f, appdata);//【像素着色器】【FRAGMENT SHADER】
	}
	if (mode==Fill3D)
	{
		v2f = VS(appdata);//【顶点着色器】【VERTEX SHADER】
		FS_Fill(v2f, appdata);//【像素着色器】【FRAGMENT SHADER】
	}
	if (mode==DEPTH3D)
	{
		v2f = VS(appdata);	//【顶点着色器】【VERTEX SHADER】
		FS_Depth(v2f, appdata);//【像素着色器】【FRAGMENT SHADER】
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
	if (r1 < 0 && r2 < 0 && r3 < 0)return true;//这里改为-0.1而不是0的原因是为了避免三角形边界因为精度问题而将像素舍弃出现黑点问题 为了解决问题 修改像素剔除范围
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

void Pipeline::Rasterization2d(vec4 v1,vec4 v2,vec4 v3,vec2 uv1,vec2 uv2,vec2 uv3,V2F in, bool DepthMode)
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
			if (i<width&&j<height&&i>0&&j>0)
			{
				if (barycentric(vec2{ v1.x,v1.y }, vec2{ v2.x,v2.y }, vec2{ v3.x,v3.y }, i, j))
				{
					vec2 pos = { i,j };
					vec3 barycentricz = barycentricTriangle(vec2{ v1.x,v1.y }, vec2{ v2.x,v2.y }, vec2{ v3.x,v3.y }, i, j);
					vec3 clip = vec3{ barycentricz.x/ -v1.w,barycentricz.y / -v2.w ,barycentricz.z / -v3.w };//纹理透视矫正
					clip = clip / (clip.x+ clip.y+ clip.z); //纹理透视矫正
					vec2 uv = vec2{ uv1 * clip.x +  uv2 * clip.y  + uv3 * clip.z };//UV映射
					double z = abs(1 - (-v1.z / Zdistance)) * barycentricz.x + abs(1 - (-v2.z / Zdistance)) * barycentricz.y + abs(1 - (-v3.z / Zdistance)) * barycentricz.z;//三角重心重心插值深度
					if (barycentricz.x < 0 || barycentricz.y < 0 || barycentricz.z < 0)
					{
						if (z > m_DepthBuffer->GetDepthBuffer(i, j))//深度测试 将当前像素的z值和Zbuffer的z值比较
						{
							m_DepthBuffer->UpdataDepthBuffer(pos.x, pos.y, z);//更新深度缓存
							if (DepthMode == true)
							{
								m_backBuffer->UpdataFrameBuffer(pos.x, pos.y, vec4{ z,z,z,1 });//ColorBuffer绘制深度信息
							}
							if (DepthMode == false)//ColorBuffer绘制颜色信息
							{
								//vec3 col = PixelinTriangleColor2d(vec2{ v1.x,v1.y }, vec2{ v2.x,v2.y }, vec2{ v3.x,v3.y }, i, j);
								//m_backBuffer->UpdataFrameBuffer(pos.x, pos.y, vec4{ col.x,col.y,col.z,1 });//更新颜色缓存	
								//m_backBuffer->UpdataFrameBuffer(pos.x, pos.y, vec4{ uv.x,uv.y,0,1 });//更新颜色缓存	
								if (uv.x>1||uv.y>1)
								{
									m_backBuffer->UpdataFrameBuffer(pos.x, pos.y, vec4{ 1,1,1/ 255 });//更新颜色缓存
								}
								else
								{
									vec4 col = m_shader->fragmentShader(in, uv);//【像素着色器】 
									//m_backBuffer->UpdataFrameBuffer(pos.x, pos.y, vec4{ col.x / 255,col.y / 255,col.z / 255,col.w / 255 });//更新颜色缓存	
									//m_backBuffer->UpdataFrameBuffer(pos.x, pos.y, vec4{ in.world_normal.x,in.world_normal.y,in.world_normal.z,1 });
								}			
							}
						}
					}
				}
			}
			
		}
	}
}

void Pipeline::Rasterization3dFill(vec4 v1, vec4 v2, vec4 v3, vec2 uv1, vec2 uv2, vec2 uv3, vec4 n1, vec4 n2, vec4 n3, vec4 w1 , vec4 w2, vec4 w3, vec4 t1, vec4 t2, vec4 t3, vec4 b1, vec4 b2, vec4 b3, V2F in, bool DepthMode)
{
	int bondscale = 1;//寻找三角形边框的最小范围 bondscale 放大边框 解决有的时候垂直线段即是边界导致边线被剔除导致渲染错误的情况出现
	int minx = 0, miny = 0, maxx = 0, maxy = 0, tempx = 0, tempy = 0;
	minx = std::min((int)v1.x - bondscale, std::min((int)v2.x - bondscale, (int)v3.x - bondscale));
	miny = std::min((int)v1.y - bondscale, std::min((int)v2.y - bondscale, (int)v3.y - bondscale));
	maxx = std::max((int)v1.x + bondscale, std::max((int)v2.x + bondscale, (int)v3.x + bondscale));
	maxy = std::max((int)v1.y + bondscale, std::max((int)v2.y + bondscale, (int)v3.y + bondscale));
	//遍历正方形边框 判断像素是否在三角形内 如果是 则绘制像素颜色 没有则不绘制
	double Zdistance = 20;
	for (int i = minx; i < maxx; ++i)
	{
		for (int j = miny; j < maxy; ++j)
		{
			if (i < width && j < height && i>0 && j>0)
			{
				if (barycentric(vec2{ v1.x,v1.y }, vec2{ v2.x,v2.y }, vec2{ v3.x,v3.y }, i, j))//判断像素是否在三角形内部通过才会执行片元着色操作 
				{
					vec3 barycentricz = barycentricTriangle(vec2{ v1.x,v1.y }, vec2{ v2.x,v2.y }, vec2{ v3.x,v3.y }, i, j);
					//if (barycentricz.x >= 0 || barycentricz.y >= 0 || barycentricz.z >= 0)
					//{
						vec2 pos = { i,j };
						
						vec3 clip = vec3{ barycentricz.x / -v1.w,barycentricz.y / -v2.w ,barycentricz.z / -v3.w };//纹理透视矫正
						clip = clip / (clip.x + clip.y + clip.z); //纹理透视矫正
						//【光栅化插值三角形内部所占片元数据】
						vec2 uv = vec2{ uv1 * clip.x + uv2 * clip.y + uv3 * clip.z };//UV映射插值
						vec4 normal = vec4{ n1 * barycentricz.x + n2 * barycentricz.y + n3* barycentricz.z };
						vec4 tangent = vec4{ t1 * barycentricz.x + t2 * barycentricz.y + t3 * barycentricz.z };
						vec4 bitangent = vec4{ b1 * barycentricz.x + b2 * barycentricz.y + b3 * barycentricz.z };
						mat<4, 4> TBN = { tangent,bitangent,normal ,vec4{0,0,0,1} };
						vec4 wpos = vec4{ w1 * barycentricz.x + w2 * barycentricz.y + w3 * barycentricz.z };
						
						double z = abs(1 - (-v1.z / Zdistance)) * barycentricz.x + abs(1 - (-v2.z / Zdistance)) * barycentricz.y + abs(1 - (-v3.z / Zdistance)) * barycentricz.z;//三角重心重心插值深度
						//【深度写入操作 Fragment Shader 着色】
						//像素和片元的区别：像素是电脑屏幕上的一个点只负责记录这一个点的颜色 只可唯一 而在这个点可以同时存在多个片元 片元是多个三角形携带数据组成的 多个片元根据深度决定谁是最后显示在像素上(当然透明)
						if (z > m_DepthBuffer->GetDepthBuffer(i, j))//深度测试 将当前像素的z值和Zbuffer的z值比较 如果大于buffer上的数值那么计算shader 并且将次片元的深度计入到像素
						{
							m_DepthBuffer->UpdataDepthBuffer(pos.x, pos.y, z);//更新深度缓存
							if (DepthMode == true)
							{
								m_backBuffer->UpdataFrameBuffer(pos.x, pos.y, vec4{ z,z,z,1 });//ColorBuffer绘制深度信息
							}
							if (DepthMode == false)//ColorBuffer绘制颜色信息
							{
								//vec3 col = PixelinTriangleColor2d(vec2{ v1.x,v1.y }, vec2{ v2.x,v2.y }, vec2{ v3.x,v3.y }, i, j);	
								if (uv.x > 1 || uv.y > 1)
								{
									m_backBuffer->UpdataFrameBuffer(pos.x, pos.y, vec4{ 1,1,1 / 255 });//更新颜色缓存
								}
								else
								{
									vec4 col = m_shader->fragmentShader(wpos,normal,uv,m_dirLightposition,m_dirlightColor,TBN);//【像素着色器】 
									m_backBuffer->UpdataFrameBuffer(pos.x, pos.y, vec4{ col.x ,col.y ,col.z ,1  });//更新颜色缓存	
									//【测试输出节点】
									//m_backBuffer->UpdataFrameBuffer(pos.x, pos.y, vec4{ normal.x, normal.y, normal.z,1 });//测试世界空间顶点法线
									//m_backBuffer->UpdataFrameBuffer(pos.x, pos.y, vec4{ wpos.x, wpos.y, wpos.z,1 });//测试世界空间顶点坐标
									//m_backBuffer->UpdataFrameBuffer(pos.x, pos.y, vec4{ uv.x,uv.y,0,1 });//测试模型UV	
								}
							}
						}
					//}
				}
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

void Pipeline::SetGeometry(Geometry* geo)
{ 
	//设置模型数据appdata 
	appdata.POSITION= geo->position;
	appdata.NORMAL= geo->normal;
	appdata.TEXCOORD0= geo->texcoord;
	appdata.P_INDEX= geo->p_index;
	appdata.N_INDEX= geo->n_index;
	appdata.UV_INDEX= geo->uv_index;
	//设置矩阵
	m_translate = geo->Translate;
	m_rotate = geo->Rotate;
	m_scale = geo->Scale;
}

void Pipeline::SetShader(Shader* shader)
{
	m_shader = shader;
}

void Pipeline::SetLight(DirectionLight* light)
{
	m_dirLightposition = light->pos;
	m_dirlightIntensity = light->intensity;
	m_dirlightColor = light->color;
}

void Pipeline::SetCamera(Camera* cam)
{
	m_cameranear = cam->cameranear;
	m_camerafar = cam->camerafar;
	m_fov = cam->fov;
	m_cameraposition = cam->Translate;
	m_camerarotate = cam->Rotate;
}

#pragma endregion


