#pragma once

#include "../mesh.h"

class Cube : public Mesh {
public:
	Cube(Renderer& renderer, int size=1);
};