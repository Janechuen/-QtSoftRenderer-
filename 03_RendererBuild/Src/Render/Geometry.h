#include <iostream>
#include "Mesh.h"
#include "Core.h"
#pragma once
class Geometry
{
public:
	//wwi矩阵
	vec3 Translate;
	vec3 Rotate;
	vec3 Scale;

	//模型数据
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
//void BindingTexture()//绑定模型信息
//{
//
//}
//void BindingShader()//绑定模型信息
//{
//
//}