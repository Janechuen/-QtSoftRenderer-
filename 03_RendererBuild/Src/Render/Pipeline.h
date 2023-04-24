
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
#include <Shader.h>
#include <2DShader.h>
#include <cmath>
#include <algorithm>
#include <QDebug>

class Pipeline
{
private:
	int width, height;
	SimpleShader* m_shader;
	FrameBuffer* m_frontBuffer;
	FrameBuffer* m_backBuffer;
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
public:
	Pipeline(int w, int h)
		:width(w), height(h)
		, m_shader(nullptr), m_frontBuffer(nullptr)
		, m_backBuffer(nullptr) {}
	~Pipeline();
	enum ShadingMode { Simple, Gouraud, Phong };
	enum RenderMode { Wire2D,Fill2D,Wire3D,Fill3D};//���� ��Ⱦģʽѡ��

	void initialize();//��ʼ��FrameBuffer
	void clearBuffer(const vec4 &color , bool depth =false);//��ɫ����Ļ��
	void setVertexBuffer(const std::vector<Vertex>& vertices) { m_vertices = vertices; }//���ö�������
	void setIndexBuffer(const std::vector<unsigned int>& indices) { m_indices = indices; }//������������
	void setShaderMode(ShadingMode mode);
	V2F lerp(const V2F& n1, const V2F& n2, float weight);
	//void Pipeline::bresenham2d(const V2F& from, const V2F& to);
	bool barycentric(vec2 p1, vec2 p2, vec2 p3, int x, int y);
	void bresenham2d(vec4 from, vec4 to);//��դ���׶�-�����α���-bresenham �����㷨
	void Rasterization2d(vec4 v1, vec4 v2, vec4 v3);
	vec3 PixelinTriangleColor2d(vec2 p1, vec2 p2, vec2 p3, int x, int y);
	void drawIndex(RenderMode mode);//���ƺ��ĺ��� ������Ⱦ��ˮ��<α>
	void swapBuffer();//����ǰ�󻺳� ��������backframe���л��� ������ɺ��ͨ���κ���ǰ�󽻻�buffer
	unsigned char* output() { return m_frontBuffer->GetColorBuffer(); }//��� uchar ָ�� ��Ⱦѭ����FrameOut��������շ������� 
};
