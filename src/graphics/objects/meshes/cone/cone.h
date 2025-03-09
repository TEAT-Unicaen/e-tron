#pragma once

#include "../mesh.h"

class Cone : public Mesh {
public:
	Cone(Renderer& renderer, float radius = 0.5f, float height = 1.0f, UINT slices = 20u);
};