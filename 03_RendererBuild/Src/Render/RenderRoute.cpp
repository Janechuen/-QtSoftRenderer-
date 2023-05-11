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

//Appdata RenderRoute::BindRenderingGeometry(Mesh* mesh,std::string f,Pipeline* pipeline)
//{
//	//mesh->LoadMesh(f);
//	//pipeline->SetPositionBuffer(mesh->position);//设置管线里的顶点
//	//pipeline->SetNormalBuffer(mesh->normal);
//	//pipeline->SetTexcoordBuffer(mesh->texcoord);
//	//pipeline->SetFaceBuffer(mesh->p_index, mesh->n_index, mesh->uv_index);
//	//Appdata appdata;
//	//这里判断使用什么类型的数据结构体 根据OBJ识别不同的结构体
//	//appdata.POSITION = mesh->position;
//	//appdata.NORMAL = mesh->normal;
//	//appdata.TEXCOORD0 = mesh->texcoord;
//	//appdata.P_INDEX = mesh->p_index;
//	//appdata.N_INDEX = mesh->n_index;
//	//appdata.UV_INDEX = mesh->uv_index;
//	//return appdata;
//}

void RenderRoute::loop()
{
	//管线初始化
	pipeline->initialize();

	//std::string meshfile = "A:/PROJECT_WORKS/VS_PROJECT/QTSoftRenderer/-QtSoftRenderer-/03_RendererBuild/Concent/Model/Obj02.obj";

	//【模型 方块】
	std::string meshfile = "A:/PROJECT_WORKS/VS_PROJECT/QTSoftRenderer/-QtSoftRenderer-/03_RendererBuild/Concent/Model/Cube.obj";
	vec3 translate = vec3{ 0,0,3 };
	vec3 rotate = vec3{ 20,0,0 };//220 * 3.14 / 180.f;
	vec3 scale = vec3{ 1,1,1 };
	vec3 translate1 = vec3{ 3,0,7 };
	vec3 rotate1 = vec3{ 20,0,0 };//220 * 3.14 / 180.f;
	vec3 scale1 = vec3{ 0.8,0.8,0.8 };
	
	//【模型 吉普车】
	//std::string meshfile = "A:/PROJECT_WORKS/VS_PROJECT/QTSoftRenderer/-QtSoftRenderer-/03_RendererBuild/Concent/Model/UAZ_Bobik.obj";
	//vec3 translate = vec3{ 0,-5,15 };
	//vec3 rotate = vec3{ 20,0,0 };//220 * 3.14 / 180.f;
	//vec3 scale = vec3{ 0.1,0.1,0.1 };
	//vec3 campos = vec3{ 0,0,-10 };
	//vec3 camrote = vec3{ 0,0,0 };
	Geometry* geo01 = new Geometry();//创建渲染几何体
	geo01->SetMesh(meshfile, translate, rotate, scale);
	geolist.push_back(geo01);

	Geometry* geo02 = new Geometry();//创建渲染几何体
	geo02->SetMesh(meshfile, translate1, rotate1, scale1);
	geolist.push_back(geo02);

	vec3 campos = vec3{ 0,0,-10 };
	vec3 camrote = vec3{ 0,0,0 };
	while (!stopped)
	{
		pipeline->clearBuffer(vec4{ 0, 0, 0, 1.0f });//渲染循环While内将上一帧绘制好的图像清空为默认颜色 这里填充为黑色
		geo01->SetRotate(0.01);
		Camera* cam = new Camera();//相机初始化
		cam->SetCamera(0.3, 50, 90 * 3.14 / 180.f, campos, camrote);
		//【渲染环节】
		
		pipeline->SetCamera(cam);
		//这里要计算有多少个模型 完了再安排绘制
		for (int i =0;i<geolist.size();i++)
		{
			pipeline->SetGeometry(geolist[i]);//
			pipeline->drawIndex(Pipeline::Fill3D);  //渲染循环While内核心函数：负责绘制图像
			   //双缓冲交换 因为DrawIndex绘制的是back 	
		}
		pipeline->swapBuffer();
		emit RenderRoute::frameOut(pipeline->output());
	}
}