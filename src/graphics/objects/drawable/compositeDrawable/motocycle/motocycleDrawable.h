#pragma once

#include "graphics/objects/drawable/compositeDrawable/compositeDrawable.h"
#include "../../instancedMeshDrawable/instancedMeshDrawable.h"
#include "../../singleMeshDrawable/singleMeshDrawable.h"

#include "../../../light.h"

#include "../../../meshes/meshes.h"

class MotocycleDrawable : public CompositeDrawable {
public:
	MotocycleDrawable(Renderer& renderer, dx::XMFLOAT3 position, dx::XMFLOAT3 rotation, Color playerColor, Color baseColor);
	
	void update(float delta) noexcept override;
	std::shared_ptr<Light> getLight() const noexcept;
private:
	std::shared_ptr<Light> pLight;
};