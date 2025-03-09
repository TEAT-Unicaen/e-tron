#pragma once

#include "../mesh.h"

class Sphere : public Mesh {
public:
	Sphere(Renderer& renderer, float radius=0.5f, UINT sliceCount=20, UINT stackCount=20);

};