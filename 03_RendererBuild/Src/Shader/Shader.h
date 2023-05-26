#pragma once
#ifndef SHADER_H
#define SHADER_H
#include <Mesh.h>
#include <V2F.h>
#include <Core.h>
#include "Texture.h"
#include "ShaderLibray.h"
class Shader
{
public:
	Shader() {}
	~Shader() {}
	V2F vertexShader(const Vertex& in);//����Shader
	vec4 fragmentShader(const V2F& in, vec2 uv);//����Shader
	vec4 fragmentShader(vec4 worldposition, vec4 worldnormal, vec2 uv, vec4 lightposition, vec4 lightcolor);//����Shader
	enum TextureMode { DiffuseTex, NormalTex };//����ģʽ
	void SetTexture(std::string path, TextureMode mode);//��������
	TGAColor sample2D(const TGAImage img, vec2& uvf);//��������
private:
	TGAImage diffusemap{};         // diffuse color texture
	TGAImage normalmap{};          // normal map texture
	TGAImage specularmap{};        // specular map texture
};

#endif // SHADER_H