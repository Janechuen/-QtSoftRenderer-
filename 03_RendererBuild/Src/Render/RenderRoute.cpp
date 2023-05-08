#include "RenderRoute.h"

RenderRoute::RenderRoute(int w, int h, QObject* parent)
	: QObject(parent), width(w), height(h), channel(4)
{
	stopped = false;
	pipeline = new Pipeline(width, height);
}

void RenderRoute::stopIt() {
	stopped = true;
}

Appdata RenderRoute::BindRenderingGeometry(Mesh* mesh,std::string f,Pipeline* pipeline)
{
	mesh->LoadMesh(f);
	pipeline->SetPositionBuffer(mesh->position);//���ù�����Ķ���
	pipeline->SetNormalBuffer(mesh->normal);
	pipeline->SetTexcoordBuffer(mesh->texcoord);
	pipeline->SetFaceBuffer(mesh->p_index, mesh->n_index, mesh->uv_index);
	Appdata appdata;
	//�����ж�ʹ��ʲô���͵����ݽṹ�� ����OBJʶ��ͬ�Ľṹ��
	appdata.POSITION = mesh->position;
	appdata.NORMAL = mesh->normal;
	appdata.TEXCOORD0 = mesh->texcoord;
	appdata.P_INDEX = mesh->p_index;
	appdata.N_INDEX = mesh->n_index;
	appdata.UV_INDEX = mesh->uv_index;
	return appdata;
}

void RenderRoute::loop()
{
	pipeline->initialize();
	//vec4 v1{ 100, 100, 0,0 }, v2{ 1200, 200, 0,0 }, v3{ 500, 700, 0 ,0};
	//vec4 v1{ 0, 0, 0,0 }, v2{ 1920, 1080, 0,0 }, v3{ 500, 700, 0 ,0 }; //���߲���
	//Mesh* msh = new Mesh;
	//msh->triangle(v1, v2, v3);
	//pipeline->setVertexBuffer(msh->vertices);
	//pipeline->setIndexBuffer(msh->index);
	//Mesh* Cube = new Mesh;
	//Cube->LoadMesh("A:/PROJECT_WORKS/VS_PROJECT/QTSoftRenderer/-QtSoftRenderer-/03_RendererBuild/Concent/Model/Cube.obj");

	while (!stopped)
	{
		/*
		ģ�ͼ��� ׼��
		*/
		Mesh* mesh = new Mesh;
		std::string meshfile= "A:/PROJECT_WORKS/VS_PROJECT/QTSoftRenderer/-QtSoftRenderer-/03_RendererBuild/Concent/Model/Cube.obj";
		//std::string meshfile = "A:/PROJECT_WORKS/VS_PROJECT/QTSoftRenderer/-QtSoftRenderer-/03_RendererBuild/Concent/Model/UAZ_Bobik.obj";
		Appdata a = BindRenderingGeometry(mesh, meshfile, pipeline);
		/*
		����Ⱦ���ڡ�
		*/ 
		//��Ⱦѭ��While�ڽ���һ֡���ƺõ�ͼ�����ΪĬ����ɫ �������Ϊ��ɫ
		pipeline->clearBuffer(vec4{0, 0, 0, 1.0f});
		//��Ⱦѭ��While�ں��ĺ������������ͼ��
		pipeline->drawIndex(Pipeline::Fill3D,a);
		//˫���彻�� ��ΪDrawIndex���Ƶ���back 
		pipeline->swapBuffer();
		emit RenderRoute::frameOut(pipeline->output());
	}
}