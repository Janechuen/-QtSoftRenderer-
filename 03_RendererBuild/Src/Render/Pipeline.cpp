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
    m_shader = new SimpleShader(); //������� Ĭ������shader
}

V2F Pipeline::VS(Appdata a)
{
	//�������� ������ӱ��ؿռ�任�� ���� ��� ͶӰ ��󵽲ü��ռ� ��Ļ�ռ�
	V2F VS_Output;
	mat<4, 4>TransformMatrix = GetTransformMatrix();
	mat<4, 4>ViewMatrix = GetViewMatrix({ 0,0,-10 }, { 0,0,0 }, { 0,1,0 });
	double near = 0.3;
	double far = 50;
	mat<4, 4>ProjectionMatrix = GetProjectionMatrix((double)width / (double)height, 90 * 3.14 / 180.f, near, far);
	//������ɫ��ѭ�� ���ÿ��������л�����MVP����
	for (int i = 0; i < a.POSITION.size(); i++)
	{
		//MVP�任
		vec4 VSOutput_Pos = vec4{ a.POSITION[i].x,a.POSITION[i].y,a.POSITION[i].z,1.0 };
		VSOutput_Pos = TransformMatrix * VSOutput_Pos;//M�任 ��ģ�Ϳռ��������ռ�
		VSOutput_Pos = ViewMatrix * VSOutput_Pos; //V�任 ������ռ�����ӿڿռ�
		VSOutput_Pos = ProjectionMatrix * VSOutput_Pos; //P�任 ���ӿڿռ������׶�ü��ռ�
		VS_Output.position.push_back(VSOutput_Pos);
		vec4 Cs_Pos = VSOutput_Pos;
		Cs_Pos = vec4{ Cs_Pos.x / Cs_Pos.w, Cs_Pos.y / Cs_Pos.w, Cs_Pos.z / Cs_Pos.w, Cs_Pos.w };//Perspectivedivide͸�ӳ��� xyz/w ����NDC�ռ�
		Cs_Pos = vec4{ (width * Cs_Pos.x / 2) + width / 2,(height * Cs_Pos.y / 2) + height / 2 ,0,0 };//viewportmapping�ӿ�Ƭ��
		//m_backBuffer->UpdataFrameBuffer(Cs_Pos.x, Cs_Pos.y, vec4{ 1,0,1,1 });
		VS_Output.screen_position.push_back(Cs_Pos);
	}
	return VS_Output;
}

void Pipeline::FS_Wire(V2F in, Appdata a)
{
	for (int i = 0; i < a.P_INDEX.size(); i += 3)//��ȡģ��λ������
	{
		std::vector<vec4> aa = in.screen_position;//����������
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
	for (int i = 0; i < a.P_INDEX.size(); i += 3)//��ȡģ��λ������
	{
		std::vector<vec4> aa = in.screen_position;//����������
		vec4 pointa = in.screen_position[a.P_INDEX[i]];
		vec4 pointb = in.screen_position[a.P_INDEX[i + 1]];
		vec4 pointc = in.screen_position[a.P_INDEX[i + 2]];
		Rasterization2d(pointa, pointb, pointc);
	}
}

void Pipeline::drawIndex(RenderMode mode, Appdata a)
{
    //�������Ϊ�� ��ִ�л��Ʋ���
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
		//��������ɫ������VERTEX SHADER��
		V2F vs = VS(a);
		//��������ɫ������FRAGMENT SHADER��
		FS_Wire(vs,a);
		
	}
	if (mode== Fill3D)
	{
		//��������ɫ������VERTEX SHADER��
		V2F vs = VS(a);
		//��������ɫ������FRAGMENT SHADER��
		FS_Fill(vs, a);
	}
	else
	{
		qDebug() << "����PipeLine.Drawindwx ��ȾģʽRenderModeΪ�� �������������Ⱦѭ���еĵ���";
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
       m_shader = new SimpleShader();//������� Ĭ������shader
    else if(mode==Phong);
}

void Pipeline::swapBuffer()//����buffer
{
    FrameBuffer* tmp = m_frontBuffer;
    m_frontBuffer = m_backBuffer;
    m_backBuffer = tmp;
}

#pragma region 2D��դ��
//2D �߿��դ��ģʽ
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
//2D ��դ��������
bool Pipeline::barycentric(vec2 p1, vec2 p2, vec2 p3, int x, int y)
{
	vec2 P = { x,y };
	vec2 AB = p2 - p1; vec2 BC = p3 - p2; vec2 CA = p1 - p3;
	printf("AB��%d", AB);
	vec2 AP = P - p1; vec2 BP = P - p2; vec2 CP = P - p3;
	int r1 = cross_2(AB, AP), r2 = cross_2(BC, BP), r3 = cross_2(CA, CP);
	if (!r1 || !r2 || !r3) return true; // =0��� ���� p���������α�Ե��
	if (r1 > 0 && r2 > 0 && r3 > 0)return true; //������� ͬ������Ϊ�������η�Χ��
	if (r1 < 0 && r2 < 0 && r3 < 0)return true;
	return false;
}

void Pipeline::Rasterization2d(vec4 v1,vec4 v2,vec4 v3)
{
	//Ѱ�������α߿����С��Χ
	int minx = 0, miny = 0, maxx = 0, maxy = 0, tempx = 0, tempy = 0;
	minx = std::min((int)v1.x, std::min((int)v2.x, (int)v3.x));
	miny = std::min((int)v1.y, std::min((int)v2.y, (int)v3.y));
	maxx = std::max((int)v1.x, std::max((int)v2.x, (int)v3.x));
	maxy = std::max((int)v1.y, std::max((int)v2.y, (int)v3.y));
	//���������α߿� �ж������Ƿ����������� ����� �����������ɫ û���򲻻���
	for (int i = minx; i < maxx; ++i)
	{
		for (int j = miny; j < maxy; ++j)
		{
			if (barycentric(vec2{ v1.x,v1.y }, vec2{ v2.x,v2.y }, vec2{ v3.x,v3.y }, i, j))
			{
				vec2 pos = { i,j };
				vec3 col = PixelinTriangleColor2d(vec2{ v1.x,v1.y }, vec2{ v2.x,v2.y }, vec2{ v3.x,v3.y }, i, j);
				m_backBuffer->UpdataFrameBuffer(pos.x, pos.y, vec4{1,1,1,1});
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

#pragma region 3D��դ��

#pragma endregion

