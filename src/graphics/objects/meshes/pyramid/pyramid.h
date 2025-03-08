#pragma once

#include "../mesh.h"

class Pyramid : public Mesh {
public:
	Pyramid(Renderer& renderer, int size=1);
};