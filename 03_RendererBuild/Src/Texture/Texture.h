#pragma once
#include <iostream>
#include "Core.h"
#include "TgaImage.h"
class Texture
{
	
private:
	TGAImage diffusemap{};         // diffuse color texture
	TGAImage normalmap{};          // normal map texture
	TGAImage specularmap{};        // specular map texture
public:
	void LoadTexture(std::string path);
	Texture(std::string path)
	{
		diffusemap.read_tga_file(path.c_str());
	}
	TGAImage GetDiffuseTexture()
	{
		return diffusemap;
	}


};

