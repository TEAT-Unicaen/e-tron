#pragma once

#include "graphics/objects/drawable/compositeDrawable/compositeDrawable.h"
#include "../../instancedMeshDrawable/instancedMeshDrawable.h"
#include "../../singleMeshDrawable/singleMeshDrawable.h"

#include "../../../meshes/meshes.h"

class MotocycleDrawable : public CompositeDrawable {
public:
	MotocycleDrawable(Renderer& renderer, dx::XMFLOAT3 position, dx::XMFLOAT3 rotation, Color color);
};