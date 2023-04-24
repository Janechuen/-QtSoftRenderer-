#pragma once
#ifndef SHADER_H
#define SHADER_H
#include <Mesh.h>
#include <V2F.h>
#include <Core.h>
class Shader
{
public:
	Shader() {}
	virtual ~Shader() {}
	virtual V2F vertexShader(const Vertex& in) = 0;
	virtual vec4 fragmentShader(const V2F& in) = 0;
};

#endif // SHADER_H