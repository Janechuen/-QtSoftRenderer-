
/*
Pipe���߿���
LightMode ����ģʽ
��դ������������<��� ���>
FrameBuffer������
����Frame Buffer ˫����<Front Back>
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
	//FrameBuffer ����
	////-------------------------------------------//-------------------------------------------
	int width, height;
	Shader* m_shader;
	FrameBuffer* m_frontBuffer;//ǰ�����ػ���
	FrameBuffer* m_backBuffer;//�������ػ���
	FrameBuffer* m_DepthBuffer;//��Ȼ���
	//-------------------------------------------//-------------------------------------------
	//3Dģ������
	//-------------------------------------------//-------------------------------------------
	Appdata appdata;//���ν׶���Ҫ������
	/*std::vector<vec3>t_position;
	std::vector<vec3>t_normal;
	std::vector<vec2>t_texcoord;
	std::vector<int>tp_index;
	std::vector<int>tn_index;
	std::vector<int>tuv_index;*/
	std::string t_vs;
	std::string t_fs;
	//-------------------------------------------//-------------------------------------------
	//������Ϣ
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
	enum RenderMode { Wire2D,Fill2D,Wire3D,Fill3D,DEPTH3D};//���� ��Ⱦģʽѡ��

	void initialize();//��ʼ��FrameBuffer
	void clearBuffer(const vec4 &color);//��ɫ����Ļ��
	//����ģ������
	//void SetPositionBuffer(const std::vector<vec3>& position) { t_position = position; }
	//void SetNormalBuffer(const std::vector<vec3>& normal) { t_normal = normal; }
	//void SetTexcoordBuffer(const std::vector<vec2>& texcoord) { t_texcoord = texcoord; }
	//void SetFaceBuffer(const std::vector<int>& p, const std::vector<int>& n, const std::vector<int>& t)
	//{ tp_index = p, tn_index = n, tuv_index = t; }
	void SetShader(const std::string vs, const std::string fs) { t_vs = vs, t_fs = fs; }
	void setShaderMode(ShadingMode mode);

#pragma region 3D��Ⱦ-MVP
	mat<4, 4> GetTransformMatrix()//3D ģ�ͱ任
	{
		//double time = FF_time();
		vec3 scale = m_scale;
		vec3 tran = m_translate;
		double rotate = m_rotate.x;
		mat<4, 4>S = { vec4{scale.x,0,0,0},vec4{0,scale.y,0,0},vec4{0,0,scale.z,0},vec4{0,0,0,1} };//��ά���ž���
		mat<4, 4>R = { vec4{cos(rotate),0,sin(rotate),0},vec4{0,1,0,0},vec4{-sin(rotate),0,cos(rotate),0},vec4{0,0,0,1} };//TODO�� 3D��ת����ʵ�� �Ȳ���
		mat<4, 4>T = { vec4{1,0,0,tran.x},vec4{0,1,0,tran.y},vec4{0,0,1,tran.z},vec4{0,0,0,1} };
		mat<4, 4>TempMatrix = T * R * S;
		return TempMatrix;
	}
	mat<4, 4> GetViewMatrix(const vec3 eye, const vec3 pos, const vec3 up)//3D �ӿڱ任
	{
		vec3 z = (pos - eye).normalized();
		vec3 x = cross(up, z).normalized();
		vec3 y = cross(z, x).normalized();
		mat<4, 4> R = { {vec4{x.x,x.y,x.z,0},vec4{y.x,y.y,y.z,0},vec4{z.x,z.y,z.z,0},vec4{0,0,0,1}} };
		mat<4, 4> T = { {vec4{1,0,0,-eye.x},vec4{0,1,0,-eye.y},vec4{0,0,1,-eye.z},vec4{0,0,0,1}} };
		return  T;
	}
	mat<4, 4> GetProjectionMatrix( double aspect,  double fov,  double n,  double f)//ͶӰ����
	{
		return { {vec4{tan(3.1415926 / 2 - (fov/2))/ aspect,0,0,0}, vec4{0,1/ tan(3.1415926 / 2 - (fov / 2)),0,0}, vec4{0,0,-((f+n)/(f-n)),-((2*n*f)/(f-n))}, vec4{0,0,-1,0}} };
	}
	mat<4, 4> Viewport(const int x, const int y, const int w, const int h)//͸�ӳ���+�ӿڱ任
	{
		mat<4, 4> temp = { {vec4{w / 2., 0, 0, (double)(x + w / 2)}, vec4{0, h / 2., 0, (double)(y + h / 2)}, vec4{0,0,1,0}, vec4{0,0,0,1}} };
		return	temp;
	}
#pragma endregion

#pragma region 3D��Ⱦ-��ɫ��
	V2F VS(Appdata in);//���ν׶�
	void FS_Wire(V2F in,Appdata a);//��դ���׶� �߿�ģʽ
	void FS_Fill(V2F in, Appdata a);//��դ���׶� ����ģʽ
	void FS_Depth(V2F in, Appdata a);//��դ���׶� ���ģʽ
#pragma endregion

#pragma region 3D��Ⱦ-��Ż�
	bool BackfaceCulling(vec4 v1, vec4 v2, vec4 v3);//�����޳�����
	bool barycentric(vec2 p1, vec2 p2, vec2 p3, int x, int y);
	vec3 barycentricTriangle(vec2 p1, vec2 p2, vec2 p3, int x, int y);
	void bresenham2d(vec4 from, vec4 to);//��դ���׶�-�����α���-bresenham �����㷨
	void Rasterization2d(vec4 v1, vec4 v2, vec4 v3,bool DepthMode);
	vec3 PixelinTriangleColor2d(vec2 p1, vec2 p2, vec2 p3, int x, int y);
#pragma endregion

#pragma region 3D-��Ⱦ��������
	void SetGeometry(Geometry* geo);//����ģ������ 
	void SetCamera(Camera* cam );
	void drawIndex(RenderMode mode);//���ƺ��ĺ��� ������Ⱦ��ˮ��<α>
	void swapBuffer();//����ǰ�󻺳� ��������backframe���л��� ������ɺ��ͨ���κ���ǰ�󽻻�buffer
	unsigned char* output() { return m_frontBuffer->GetColorBuffer(); }//��� uchar ָ�� ��Ⱦѭ����FrameOut��������շ������� 
#pragma endregion

};
