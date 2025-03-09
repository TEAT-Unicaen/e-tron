#pragma once

#include "../mesh.h"

class Plane : public Mesh {
public:
	Plane(Renderer& renderer, float width=1, float height=1, UINT nWidth=1, UINT nHeight=1);

};