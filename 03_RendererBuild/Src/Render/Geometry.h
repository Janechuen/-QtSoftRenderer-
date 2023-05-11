#include <iostream>
#include "Mesh.h"
#include "Core.h"
#pragma once
class Geometry
{
public:
	//wwi����
	vec3 Translate;
	vec3 Rotate;
	vec3 Scale;

	//ģ������
	std::vector<vec3>position;
	std::vector<vec3>normal;
	std::vector<vec2>texcoord;
	std::vector<int>p_index;
	std::vector<int>n_index;
	std::vector<int>uv_index;

	Geometry() {}
	~Geometry() {}
	void SetRotate(double f);
	void SetMesh(std::string meshfile, vec3 t, vec3 r, vec3 s);
private:
	
};


//geometry::~geometry()
//{
//}
//
//void BindingTexture()//��ģ����Ϣ
//{
//
//}
//void BindingShader()//��ģ����Ϣ
//{
//
//}