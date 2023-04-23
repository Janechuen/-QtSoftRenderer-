#pragma once
#include <iostream> 
#include <vector>
#include <cassert>
#include <cmath>
#include <Core.h>
class Mesh 
{	
public:
	//临时 绘制点用 测试加载是否生效
	Mesh(std::vector<vec2> &mesh);
	vec2 triangle;
	std::vector<vec3> verts{};
	std::vector<vec2> triangleverts{};
	//Mesh(const std::string filename);

};