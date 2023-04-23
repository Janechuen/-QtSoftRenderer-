#pragma once
#include <iostream> 
#include <vector>
#include <cassert>
#include <cmath>
#include <Core.h>
class Mesh 
{	
public:
	//��ʱ ���Ƶ��� ���Լ����Ƿ���Ч
	Mesh(std::vector<vec2> &mesh);
	vec2 triangle;
	std::vector<vec3> verts{};
	std::vector<vec2> triangleverts{};
	//Mesh(const std::string filename);

};