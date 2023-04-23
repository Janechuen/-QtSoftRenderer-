#include <Mesh.h>

Mesh::Mesh(std::vector<vec2> &mesh)
{
	for (const auto& vec : mesh)
	{
		triangleverts.push_back(vec);
	}

}
