#include "Geometry.h"

void Geometry::SetMesh(std::string meshfile, vec3 t, vec3 r, vec3 s)
{
	Mesh mesh;
	mesh.LoadMesh(meshfile);
	position = mesh.position;
	normal = mesh.normal;
	texcoord = mesh.texcoord;
	p_index = mesh.p_index;
	n_index = mesh.n_index;
	uv_index = mesh.uv_index;

	Translate = t;
	Rotate = r;
	Scale = s;
}

void Geometry::SetRotate(double f)
{
	Rotate.x = (Rotate.x + f);
	Rotate.y = (Rotate.y + f);
	Rotate.z = (Rotate.z + f);
}
