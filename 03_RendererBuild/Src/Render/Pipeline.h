
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
	enum RenderMode { Wire2D,Fill2D,Wire3D,Fill3D};//核心 渲染模式选择

	void initialize();//初始化FrameBuffer
	void clearBuffer(const vec4 &color , bool depth =false);//清色除屏幕颜
	void setVertexBuffer(const std::vector<Vertex>& vertices) { m_vertices = vertices; }//设置顶点数据
	void setIndexBuffer(const std::vector<unsigned int>& indices) { m_indices = indices; }//设置索引数据
	void setShaderMode(ShadingMode mode);
	V2F lerp(const V2F& n1, const V2F& n2, float weight);
	//void Pipeline::bresenham2d(const V2F& from, const V2F& to);
	bool barycentric(vec2 p1, vec2 p2, vec2 p3, int x, int y);
	void bresenham2d(vec4 from, vec4 to);//光栅化阶段-三角形遍历-bresenham 画线算法
	void Rasterization2d(vec4 v1, vec4 v2, vec4 v3);
	vec3 PixelinTriangleColor2d(vec2 p1, vec2 p2, vec2 p3, int x, int y);
	void drawIndex(RenderMode mode);//绘制核心函数 启动渲染流水线<伪>
	void swapBuffer();//交换前后缓冲 我们是在backframe进行绘制 绘制完成后会通过次函数前后交换buffer
	unsigned char* output() { return m_frontBuffer->GetColorBuffer(); }//输出 uchar 指针 渲染循环的FrameOut函数会接收返回数据 
};
