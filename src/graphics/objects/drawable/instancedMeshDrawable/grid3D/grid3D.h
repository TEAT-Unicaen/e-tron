#pragma once

#include "../instancedMeshDrawable.h"

class Grid3D : public InstancedMeshDrawable {
public:
	Grid3D(Renderer& renderer, UINT lenght, UINT width, Mesh& mesh);

protected:
	UINT lenght;
	UINT width;
	Mesh& mesh;
};
