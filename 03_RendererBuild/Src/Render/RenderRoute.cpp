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

void RenderRoute::loop()
{
	////管线初始化
	pipeline->initialize();

	////【模型 方块01】
	////std::string meshfile = "A:/PROJECT_WORKS/VS_PROJECT/QTSoftRenderer/-QtSoftRenderer-/03_RendererBuild/Concent/Model/Cube.obj";
	//std::string meshfile = "D:/z_Work/-QtSoftRenderer-/03_RendererBuild/Concent/Model/Cube03.obj";
	//vec3 translate = vec3{ 0,1,-4 };
	//vec3 rotate = vec3{220 * 3.14 / 180.f,220 * 3.14 / 180.f,0 };//220 * 3.14 / 180.f;
	//vec3 scale = vec3{ 2,2,2 };
	//Geometry* geo01 = new Geometry();//创建渲染几何体
	//geo01->SetMesh(meshfile, translate, rotate, scale);//設置几何体
	//geolist.push_back(geo01);//将几何体压入几何体列表
	//Shader* shader01 = new Shader();//创建着色器
	////std::string diffusefile = "D:/z_Work/-QtSoftRenderer-/03_RendererBuild/Concent/Texture/S0043_GLOW_1.tga";
	//std::string diffusefile = "D:/z_Work/-QtSoftRenderer-/03_RendererBuild/Concent/Texture/D.tga";
	//std::string normalfile = "D:/z_Work/-QtSoftRenderer-/03_RendererBuild/Concent/Texture/nor03.tga";
	//shader01->SetTexture(diffusefile,Shader::DiffuseTex);
	//shader01->SetTexture(normalfile, Shader::NormalTex);
	//shaderlist.push_back(shader01); //将着色器压入着色器列表
	////【Camera相机属性】
	//Camera* cam = new Camera();//相机初始化
	//vec3 campos = vec3{ 0,1,0 };
	//vec3 camrote = vec3{ 0,0,0 };
	//cam->SetCamera(0.3, 50, 90 * 3.14 / 180.f, campos, camrote);
	////【DirectionLight属性】
	//DirectionLight* dirLight = new DirectionLight();//方向光初始化
	//dirLight->intensity = 1;
	//dirLight->pos = vec4{ 0,0,1,0 };
	//dirLight->color = vec4{ 1,0.92,0.56,0 };




	//【模型 球01】
	//std::string meshfile = "D:/z_Work/-QtSoftRenderer-/03_RendererBuild/Concent/Model/Sphere.obj";
	//vec3 translate = vec3{ 0,0,-2 };
	//vec3 rotate = vec3{0,0,0 };//220 * 3.14 / 180.f;
	//vec3 scale = vec3{ 1,1,1 };
	//Geometry* geo01 = new Geometry();//创建渲染几何体
	//geo01->SetMesh(meshfile, translate, rotate, scale);//設置几何体
	//geolist.push_back(geo01);//将几何体压入几何体列表
	//Shader* shader01 = new Shader();//创建着色器
	////std::string diffusefile = "D:/z_Work/-QtSoftRenderer-/03_RendererBuild/Concent/Texture/D.tga";
	////shader01->SetTexture(diffusefile, Shader::DiffuseTex);
	////std::string normalfile = "D:/z_Work/-QtSoftRenderer-/03_RendererBuild/Concent/Texture/nor01.tga";
	////shader01->SetTexture(normalfile, Shader::NormalTex);
	//shaderlist.push_back(shader01); //将着色器压入着色器列表
	////【Camera相机属性】
	//Camera* cam = new Camera();//相机初始化
	//vec3 campos = vec3{ 0,0,-2 };
	//vec3 camrote = vec3{ 0,0,0 };

	////【DirectionLight属性】
	//DirectionLight* dirLight = new DirectionLight();//方向光初始化
	//dirLight->intensity = 1;
	//dirLight->pos = vec4{ 1,1,-1,0 };
	//dirLight->color = vec4{ 1,0.92,0.56,0 };


	//【模型 方块02】
	//std::string cubeMeshfile = "D:/z_Work/-QtSoftRenderer-/03_RendererBuild/Concent/Model/Cube.obj";
	//vec3 translate1 = vec3{ 3,0,7 };
	//vec3 rotate1 = vec3{ 20,0,0 };//220 * 3.14 / 180.f;
	//vec3 scale1 = vec3{ 0.8,0.8,0.8 };
	//Geometry* geo02 = new Geometry();//创建渲染几何体
	//geo02->SetMesh(cubeMeshfile, translate1, rotate1, scale1);
	//geolist.push_back(geo02);
	//Shader* shader02 = new Shader();//创建着色器
	//shaderlist.push_back(shader02); //将着色器压入着色器列表

	//【模型 吉普车】
	std::string meshfile = "A:/PROJECT_WORKS/VS_PROJECT/QTSoftRenderer/-QtSoftRenderer-/03_RendererBuild/Concent/Model/UAZ_Bobik.obj";
	vec3 translate = vec3{ 0,0,0 };
	//vec3 rotate = vec3{ 90 * 3.14 / 180.f,90 * 3.14 / 180.f,0 };//220 * 3.14 / 180.f;
	vec3 rotate = vec3{ 0,200 * 3.14 / 180.f,0 };//220 * 3.14 / 180.f;
	vec3 scale = vec3{ 0.01,0.01,0.01 };
	Geometry* geo01 = new Geometry();//创建渲染几何体
	geo01->SetMesh(meshfile, translate, rotate, scale);//設置几何体
	geolist.push_back(geo01);//将几何体压入几何体列表
	Shader* shader01 = new Shader();//创建着色器
	std::string diffusefile = "D:/z_Work/-QtSoftRenderer-/03_RendererBuild/Concent/Texture/Car_01.tga";
	shader01->SetTexture(diffusefile, Shader::DiffuseTex);
	std::string normalfile = "D:/z_Work/-QtSoftRenderer-/03_RendererBuild/Concent/Texture/Car_01_N.tga";
	shader01->SetTexture(normalfile, Shader::NormalTex);
	shaderlist.push_back(shader01); //将着色器压入着色器列表
	//【Camera相机属性】
	Camera* cam = new Camera();//相机初始化
	vec3 campos = vec3{ 0,0.5,-1.5 };
	vec3 camrote = vec3{ 0,0,0 };
	cam->SetCamera(0.3, 50, 90 * 3.14 / 180.f, campos, camrote);
	//【DirectionLight属性】
	DirectionLight* dirLight = new DirectionLight();//方向光初始化
	dirLight->intensity = 1;
	dirLight->pos = vec4{ 0,0,-1,0 };
	dirLight->color = vec4{ 1,0.92,0.56,0 };


	while (!stopped)
	{
		pipeline->clearBuffer(vec4{ 0, 0, 0, 1.0f });//渲染循环While内将上一帧绘制好的图像清空为默认颜色 这里填充为黑色
		//geo01->SetRotate(0.01);
		//【渲染环节】
		
		//这里要计算有多少个模型 完了再安排绘制
		for (int i =0;i<geolist.size();i++)
		{
			pipeline->SetCamera(cam);//设置相机
			pipeline->SetGeometry(geolist[i]);//将场景几何体拖入管线渲染
			pipeline->SetShader(shaderlist[i]);//将几何体绑定的着色器拖入管线着色
			pipeline->SetLight(dirLight);
			pipeline->drawIndex(Pipeline::Fill3D);  //渲染循环While内核心函数：负责绘制图像  	
		}
		pipeline->swapBuffer();//双缓冲交换 因为DrawIndex绘制的是back 
		emit RenderRoute::frameOut(pipeline->output()); //输出Buffer 将绘制成功的Buffer法功个上级Render
	}
}