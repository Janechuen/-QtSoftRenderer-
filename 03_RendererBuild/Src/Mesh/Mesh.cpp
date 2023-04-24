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
		char trash;//trash ��һ����ʱ��������������ռλ�������ڶ����������е��ַ�
		if (!line.compare(0,2,"v "))//���Ժ���v�ַ�Ϊ����λ����Ϣ
		{
			/*
			�������ݸ�ʽ
			v -0.500000 -0.500000 0.500000
			*/
			iss >> trash;
			vec3 v;
			for(int i = 0; i < 3; i++)iss >> v[i];
			position.push_back(v);//�洢����
		}
		else if(!line.compare(0,3,"vn "))//���Ժ���vn�ַ�Ϊ���㷨����Ϣ
		{
			/*
			���㷨�����ݸ�ʽ
			vn 0.000000 0.000000 1.000000
			*/
			iss >> trash >> trash;
			vec3 n;
			for (int i = 0; i < 3; i++)iss >> n[i];
			normal.push_back(n);
		}
		else if(!line.compare(0,3, "vt "))//���Ժ���vt�ַ�Ϊ����uv��Ϣ
		{
			/*
			���㷨�����ݸ�ʽ
			vt 0.375000 0.000000
			*/
			iss >> trash >> trash;// iss>> �����ַ� ����������������Ҫ���ַ���ֻ��ȡ���õ����ݣ�������洢����Ӧ�����ݽṹ��
			vec2 uv;
			for (int i = 0; i < 2; i++)iss >> uv[i];
			texcoord.push_back({ uv.x, 1 - uv.y });
		}
		else if(!line.compare(0,2,"f "))//���Ժ���f�ַ�Ϊ��������Ϣ
		{
			/*
			�����ݸ�ʽ������ UV ���� ��������
			f 1/1/1 2/2/2 4/4/3 3/3/4
			*/
			int f, t, n;
			iss >> trash;
			int cnt;
			while (iss>>f>>trash>>t>>trash>>n)//�����ݵĶ����������������������ͷ����������ζ�ȡ���洢������
			{
				vertexindex.push_back(f);//λ������
				textureindex.push_back(t);//��������
				normalindex.push_back(n);//��������
				cnt++;
			}
			if (3!=cnt)
			{
				std::cerr << "ERROR : ģ�Ͳ�֧�ֳ����������ģ�� " << std::endl;
				return;
			}
		}
	}
	return;
}