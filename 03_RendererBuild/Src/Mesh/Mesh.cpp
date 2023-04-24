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
		char trash;//trash 是一个临时变量，它被用作占位符，用于丢弃输入流中的字符
		if (!line.compare(0,2,"v "))//测试含有v字符为顶点位置信息
		{
			/*
			顶点数据格式
			v -0.500000 -0.500000 0.500000
			*/
			iss >> trash;
			vec3 v;
			for(int i = 0; i < 3; i++)iss >> v[i];
			position.push_back(v);//存储顶点
		}
		else if(!line.compare(0,3,"vn "))//测试含有vn字符为顶点法线信息
		{
			/*
			顶点法线数据格式
			vn 0.000000 0.000000 1.000000
			*/
			iss >> trash >> trash;
			vec3 n;
			for (int i = 0; i < 3; i++)iss >> n[i];
			normal.push_back(n);
		}
		else if(!line.compare(0,3, "vt "))//测试含有vt字符为顶点uv信息
		{
			/*
			顶点法线数据格式
			vt 0.375000 0.000000
			*/
			iss >> trash >> trash;// iss>> 跳过字符 这样可以跳过不需要的字符，只提取有用的数据，并将其存储到相应的数据结构中
			vec2 uv;
			for (int i = 0; i < 2; i++)iss >> uv[i];
			texcoord.push_back({ uv.x, 1 - uv.y });
		}
		else if(!line.compare(0,2,"f "))//测试含有f字符为顶点面信息
		{
			/*
			面数据格式（顶点 UV 法线 的索引）
			f 1/1/1 2/2/2 4/4/3 3/3/4
			*/
			int f, t, n;
			iss >> trash;
			int cnt;
			while (iss>>f>>trash>>t>>trash>>n)//面数据的顶点索引、纹理坐标索引和法线索引依次读取并存储到变量
			{
				vertexindex.push_back(f);//位置索引
				textureindex.push_back(t);//纹理索引
				normalindex.push_back(n);//法线索引
				cnt++;
			}
			if (3!=cnt)
			{
				std::cerr << "ERROR : 模型不支持超过三角面的模型 " << std::endl;
				return;
			}
		}
	}
	return;
}