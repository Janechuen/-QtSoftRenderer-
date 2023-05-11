
/*
Pipe管线控制
LightMode 光照模式
光栅化三角形设置<描边 填充>
FrameBuffer类设置
基于Frame Buffer 双缓冲<Front Back>
*/
//#ifndef  PIPELINE_H
//#define  PIPELINE_H
#include <FrameBuffer.h>
#include <Core.h>
#include "Geometry.h"
#include <Appdata.h>
#include <Shader.h>
#include <cmath>
#include <algorithm>
#include <QDebug>
#include "Camera.h"

class Pipeline
{
private:
	//FrameBuffer 创建
	////-------------------------------------------//-------------------------------------------
	int width, height;
	Shader* m_shader;
	FrameBuffer* m_frontBuffer;//前向像素画布
	FrameBuffer* m_backBuffer;//后向像素画布
	FrameBuffer* m_DepthBuffer;//深度画布
	//-------------------------------------------//-------------------------------------------
	//3D模型数据
	//-------------------------------------------//-------------------------------------------
	Appdata appdata;//几何阶段需要的数据
	/*std::vector<vec3>t_position;
	std::vector<vec3>t_normal;
	std::vector<vec2>t_texcoord;
	std::vector<int>tp_index;
	std::vector<int>tn_index;
	std::vector<int>tuv_index;*/
	std::string t_vs;
	std::string t_fs;
	//-------------------------------------------//-------------------------------------------
	//矩阵信息
	//-------------------------------------------//-------------------------------------------
	vec3 m_translate; 
	vec3 m_rotate;
	vec3 m_scale;
	vec3 m_cameraposition;
	vec3 m_camerarotate;
	double m_cameranear;
	double m_camerafar;
	double m_fov;

public:
	Pipeline(int w, int h)
		:width(w), height(h)
		, m_frontBuffer(nullptr)
		, m_backBuffer(nullptr) {}
	~Pipeline();
	enum ShadingMode { Simple, Gouraud, Phong };
	enum RenderMode { Wire2D,Fill2D,Wire3D,Fill3D,DEPTH3D};//核心 渲染模式选择

	void initialize();//初始化FrameBuffer
	void clearBuffer(const vec4 &color);//清色除屏幕颜
	//设置模型属性
	//void SetPositionBuffer(const std::vector<vec3>& position) { t_position = position; }
	//void SetNormalBuffer(const std::vector<vec3>& normal) { t_normal = normal; }
	//void SetTexcoordBuffer(const std::vector<vec2>& texcoord) { t_texcoord = texcoord; }
	//void SetFaceBuffer(const std::vector<int>& p, const std::vector<int>& n, const std::vector<int>& t)
	//{ tp_index = p, tn_index = n, tuv_index = t; }
	void SetShader(const std::string vs, const std::string fs) { t_vs = vs, t_fs = fs; }
	void setShaderMode(ShadingMode mode);

#pragma region 3D渲染-MVP
	mat<4, 4> GetTransformMatrix()//3D 模型变换
	{
		//double time = FF_time();
		vec3 scale = m_scale;
		vec3 tran = m_translate;
		double rotate = m_rotate.x;
		mat<4, 4>S = { vec4{scale.x,0,0,0},vec4{0,scale.y,0,0},vec4{0,0,scale.z,0},vec4{0,0,0,1} };//三维缩放矩阵
		mat<4, 4>R = { vec4{cos(rotate),0,sin(rotate),0},vec4{0,1,0,0},vec4{-sin(rotate),0,cos(rotate),0},vec4{0,0,0,1} };//TODO： 3D旋转矩阵实现 先不搞
		mat<4, 4>T = { vec4{1,0,0,tran.x},vec4{0,1,0,tran.y},vec4{0,0,1,tran.z},vec4{0,0,0,1} };
		mat<4, 4>TempMatrix = T * R * S;
		return TempMatrix;
	}
	mat<4, 4> GetViewMatrix(const vec3 eye, const vec3 pos, const vec3 up)//3D 视口变换
	{
		vec3 z = (pos - eye).normalized();
		vec3 x = cross(up, z).normalized();
		vec3 y = cross(z, x).normalized();
		mat<4, 4> R = { {vec4{x.x,x.y,x.z,0},vec4{y.x,y.y,y.z,0},vec4{z.x,z.y,z.z,0},vec4{0,0,0,1}} };
		mat<4, 4> T = { {vec4{1,0,0,-eye.x},vec4{0,1,0,-eye.y},vec4{0,0,1,-eye.z},vec4{0,0,0,1}} };
		return  T;
	}
	mat<4, 4> GetProjectionMatrix( double aspect,  double fov,  double n,  double f)//投影矩阵
	{
		return { {vec4{tan(3.1415926 / 2 - (fov/2))/ aspect,0,0,0}, vec4{0,1/ tan(3.1415926 / 2 - (fov / 2)),0,0}, vec4{0,0,-((f+n)/(f-n)),-((2*n*f)/(f-n))}, vec4{0,0,-1,0}} };
	}
	mat<4, 4> Viewport(const int x, const int y, const int w, const int h)//透视除法+视口变换
	{
		mat<4, 4> temp = { {vec4{w / 2., 0, 0, (double)(x + w / 2)}, vec4{0, h / 2., 0, (double)(y + h / 2)}, vec4{0,0,1,0}, vec4{0,0,0,1}} };
		return	temp;
	}
#pragma endregion

#pragma region 3D渲染-著色器
	V2F VS(Appdata in);//几何阶段
	void FS_Wire(V2F in,Appdata a);//光栅化阶段 线框模式
	void FS_Fill(V2F in, Appdata a);//光栅化阶段 正常模式
	void FS_Depth(V2F in, Appdata a);//光栅化阶段 深度模式
#pragma endregion

#pragma region 3D渲染-光柵化
	bool BackfaceCulling(vec4 v1, vec4 v2, vec4 v3);//背面剔除方法
	bool barycentric(vec2 p1, vec2 p2, vec2 p3, int x, int y);
	vec3 barycentricTriangle(vec2 p1, vec2 p2, vec2 p3, int x, int y);
	void bresenham2d(vec4 from, vec4 to);//光栅化阶段-三角形遍历-bresenham 画线算法
	void Rasterization2d(vec4 v1, vec4 v2, vec4 v3,bool DepthMode);
	vec3 PixelinTriangleColor2d(vec2 p1, vec2 p2, vec2 p3, int x, int y);
#pragma endregion

#pragma region 3D-渲染管线流程
	void SetGeometry(Geometry* geo);//设置模型数据 
	void SetCamera(Camera* cam );
	void drawIndex(RenderMode mode);//绘制核心函数 启动渲染流水线<伪>
	void swapBuffer();//交换前后缓冲 我们是在backframe进行绘制 绘制完成后会通过次函数前后交换buffer
	unsigned char* output() { return m_frontBuffer->GetColorBuffer(); }//输出 uchar 指针 渲染循环的FrameOut函数会接收返回数据 
#pragma endregion

};
