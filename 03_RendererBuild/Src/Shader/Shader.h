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
	V2F vertexShader(const Vertex& in);//顶点Shader
	vec4 fragmentShader(const V2F& in, vec2 uv);//像素Shader
	vec4 fragmentShader(vec4 worldposition, vec4 worldnormal, vec2 uv, vec4 lightposition, vec4 lightcolor);//像素Shader
	enum TextureMode { DiffuseTex, NormalTex };//纹理模式
	void SetTexture(std::string path, TextureMode mode);//设置纹理
	TGAColor sample2D(const TGAImage img, vec2& uvf);//采样纹理
private:
	TGAImage diffusemap{};         // diffuse color texture
	TGAImage normalmap{};          // normal map texture
	TGAImage specularmap{};        // specular map texture
};

#endif // SHADER_H