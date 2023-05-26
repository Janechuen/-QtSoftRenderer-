#include "Shader.h"
V2F Shader::vertexShader(const Vertex& in) {
	V2F ret;
	//ret.posM2W = in.Position;
	//ret.posV2P = in.Position;
	//ret.color = in.Color;
	//ret.normal = in.Normal;
	//ret.oneDivZ = 1.0;
	//ret.texcoord = in.texcoord0;
	return ret;
}
vec4 Shader::fragmentShader(const V2F& in,vec2 uv)
{
	vec4 Color;
	TGAColor d = sample2D(diffusemap,uv);
	Color.x = d.bgra[2] / 255;
	Color.y = d.bgra[1] / 255;
	Color.z = d.bgra[0] / 255;
	Color.w = 1;
	return Color;
}

vec4 Shader::fragmentShader(vec4 worldposition, vec4 worldnormal, vec2 uv, vec4 lightposition, vec4 lightcolor)
{
	//【纹理采样】
	TGAColor d = sample2D(diffusemap, uv);
	vec4 tex01;
	tex01.x = d.bgra[2];
	tex01.y = d.bgra[1];
	tex01.z = d.bgra[0];
	tex01.w = 1;
	tex01 = tex01 / 255;
	//【光照模型】
	vec4 lightdir = lightposition.normalized();
	lightdir.normalized();
	double nol = dot(worldnormal, lightdir);
	nol = C_MAX(nol, 0);
	//vec4 col = vec4{n,n,n,n};
	//vec4 col = lightcolor;
	vec4 col;
	col = C_Mul(lightcolor,tex01) ;
	col = col * nol;
	return col;
}

TGAColor Shader::sample2D(const TGAImage img, vec2& uvf)
{
	//return img.get(abs(1-uvf[0]) * img.width(),abs(1-uvf[1]) * img.height());
	//return img.get( uvf[0] * img.width(),  uvf[1]* img.height());
	return img.get(uvf[0]* img.width(),abs(1-uvf[1]) * img.height());//UV Y轴旋转
}

void Shader::SetTexture(std::string path, TextureMode mode)
{
	if (mode == DiffuseTex)
	{
		diffusemap.read_tga_file(path.c_str());
	}
	if (mode == NormalTex)
	{
		normalmap.read_tga_file(path.c_str());
	}
}