#pragma once
//#ifndef SHADER_H
//#define SHADER_H
#include <Mesh.h>
#include <V2F.h>
#include <Core.h>
class SimpleShader
{
public:
	SimpleShader() {}
	~SimpleShader() {}
	V2F vertexShader(const Vertex& in);
	vec4 fragmentShader(const V2F& in);
};

//#endif // SHADER_H