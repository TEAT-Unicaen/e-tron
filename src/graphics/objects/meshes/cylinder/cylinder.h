#pragma once

#include "../mesh.h"

class Cylinder : public Mesh {
public:
	Cylinder(Renderer& renderer, float radius=0.5f, float height=1.0f, UINT slices=20u);
};