#pragma once

#include "../mesh.h"

class Tore : public Mesh {
public:
	Tore(Renderer& renderer, float outrerRadius = 0.5f, float innerRadius = 0.2f, UINT sliceCount = 20, UINT stackCount = 20);
};