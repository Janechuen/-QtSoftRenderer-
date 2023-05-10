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
	pipeline->SetPositionBuffer(mesh->position);//设置管线里的顶点
	pipeline->SetNormalBuffer(mesh->normal);
	pipeline->SetTexcoordBuffer(mesh->texcoord);
	pipeline->SetFaceBuffer(mesh->p_index, mesh->n_index, mesh->uv_index);
	Appdata appdata;
	//这里判断使用什么类型的数据结构体 根据OBJ识别不同的结构体
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
	//管线初始化
	pipeline->initialize();

	while (!stopped)
	{
		/*
		模型加载 准备
		*/
		Mesh* mesh = new Mesh;
		//std::string meshfile= "A:/PROJECT_WORKS/VS_PROJECT/QTSoftRenderer/-QtSoftRenderer-/03_RendererBuild/Concent/Model/Cube.obj";
		std::string meshfile = "A:/PROJECT_WORKS/VS_PROJECT/QTSoftRenderer/-QtSoftRenderer-/03_RendererBuild/Concent/Model/UAZ_Bobik.obj";
		//std::string meshfile = "A:/PROJECT_WORKS/VS_PROJECT/QTSoftRenderer/-QtSoftRenderer-/03_RendererBuild/Concent/Model/Obj02.obj";
		Appdata a = BindRenderingGeometry(mesh, meshfile, pipeline);
		/*
		【渲染环节】
		*/ 
		//渲染循环While内将上一帧绘制好的图像清空为默认颜色 这里填充为黑色
		pipeline->clearBuffer(vec4{0, 0, 0, 1.0f});
		//渲染循环While内核心函数：负责绘制图像
		pipeline->drawIndex(Pipeline::DEPTH3D,a);
		//双缓冲交换 因为DrawIndex绘制的是back 
		pipeline->swapBuffer();
		emit RenderRoute::frameOut(pipeline->output());
	}
}