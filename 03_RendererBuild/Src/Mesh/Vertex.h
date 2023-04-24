#pragma once
#include <Core.h>
//��������ȡԭʼģ������ ����������Ϊ����
/*
* Ŀǰֻʶ�������Ϣ
01. Position ����λ����Ϣ
02. UV Texcoord ģ��UV����
03. Normal ģ�ͷ�����Ϣ
04. Color ģ�Ͷ���ɫ��Ϣ
*/
class Vertex
{
public:
	vec4 Position;
	vec2 texcoord0;
	vec3 Normal;
	vec4 Color;
	Vertex() {}//���캯��
	~Vertex() {}
	Vertex(vec4 pos, vec4 col, vec2 tex, vec3 nor) : //���ƹ��캯��
		Position(pos), Color(col), texcoord0(tex), Normal(nor) {}
	Vertex(const Vertex& ver) :  //���ƹ��캯��
		Position(ver.Position),
		Color(ver.Color),
		texcoord0(ver.texcoord0),
		Normal(ver.Normal) {}
private:

};

