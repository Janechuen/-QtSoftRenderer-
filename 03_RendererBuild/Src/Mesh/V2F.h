#pragma once
#include <Core.h>
/*
V2F��
1.���� vertex ������� �ṩ�� shader���Vertex shaderʹ��
*/
class V2F
{
public:
	//vec4 posM2W; //ģ�͵�ʱ�����
	//vec4 posV2P; 
	//vec2 texcoord;
	//vec3 normal;
	//vec4 color;
	std::vector <vec4> position;
	std::vector <vec4> screen_position;
	std::vector <vec4> view_position;
	//double oneDivZ;

	//V2F() {}
	//V2F(vec4 pMW, vec4 pVP, vec2 tex, vec3 nor, vec4 col, double oZ) :
	//	posM2W(pMW), posV2P(pVP), texcoord(tex), normal(nor), color(col), oneDivZ(oZ) {}
	//V2F(const V2F& ver) :
	//	posM2W(ver.posM2W),
	//	posV2P(ver.posV2P),
	//	texcoord(ver.texcoord),
	//	normal(ver.normal),
	//	color(ver.color),
	//	oneDivZ(ver.oneDivZ) {}
};