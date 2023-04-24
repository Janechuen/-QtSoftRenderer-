#include <Mesh.h>

Mesh& Mesh::operator=(const Mesh& msh)
{
	vertices = msh.vertices;
	index = msh.index;
	return *this;
}

void Mesh::setVertices(Vertex* v, int count)
{
	vertices.resize(static_cast<unsigned long>(count));
	new(&vertices[0])std::vector<Vertex>(v, v + count);
}

void Mesh::setIndex(int* i, int count)
{
	index.resize(static_cast<unsigned long >(count));
	new(&index)std::vector<unsigned int>(i, i + count);
}

void Mesh::triangle(vec4& v1, vec4& v2, vec4& v3)
{
	vertices.resize(3);
	index.resize(3);
	vertices[0].Position = v1;
	vertices[0].Normal = { 0.0, 0.0, 1.0 };
	vertices[0].Color = { 1.f, 0.f, 0.f, 1.f };
	vertices[0].texcoord0 = vec2{ 0.f, 0.f };
	vertices[1].Position = v2;
	vertices[1].Normal = vec3{ 0.f, 0.f, 1.f };
	vertices[1].Color = vec4{ 0.f, 1.f, 0.f, 1.f };
	vertices[1].texcoord0 = vec2{ 1.f, 0.f };
	vertices[2].Position = v3;
	vertices[2].Normal = vec3{ 0.f, 0.f, 1.f };
	vertices[2].Color = vec4{ 0.f, 0.f, 1.f, 1.f };
	vertices[2].texcoord0 = vec2{ 0.5f, 1.f };
	index[0] = 0;
	index[1] = 1;
	index[2] = 2;
}

void Mesh::LoadMesh(const std::string filename)
{
	std::ifstream in;
	in.open(filename, std::ifstream::in);
	if (in.fail())return;
	std::string line;
	while (!in.eof())
	{
		std::getline(in, line);
		std::istringstream iss(line.c_str());
		char trash;
		if (!line.compare(0,2,"v "))
		{
			iss >> trash;
			vec3 v;
			for(int i = 0; i < 3; i++)iss >> v[i];
			position.push_back(v);//´æ´¢¶¥µã
		}
		
	}
	return;
}