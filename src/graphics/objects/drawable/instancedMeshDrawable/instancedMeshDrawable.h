#pragma once

#include "../drawable.h"

class InstancedMeshDrawable : public Drawable {
public:
	InstancedMeshDrawable(const std::string& name, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material, const std::vector<dx::XMMATRIX>& modelMatrices);
	virtual void draw(const std::shared_ptr<Shader>& shader) override;

};