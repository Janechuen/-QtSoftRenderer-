#pragma once
#include "Core.h"
#include <vector>

class Appdata
{
public:
	//Appdata();
	//~Appdata();
	std::vector<vec3> POSITION;
	std::vector<vec3> NORMAL;
	std::vector<vec2> TEXCOORD0;
	std::vector<int> P_INDEX;
	std::vector<int> N_INDEX;
	std::vector<int> UV_INDEX;
private:
};


//struct appdata_base
//{
//	std::vector<vec4> POSITION;
//	std::vector<vec3> NORMAL;
//	std::vector<vec4> TEXCOORD0;
//
//};