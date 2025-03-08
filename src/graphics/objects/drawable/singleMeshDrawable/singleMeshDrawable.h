#pragma once

#include "../drawable.h"
#include "../../meshes/mesh.h"
#include "../../bindable/bindableBase.h"

class SingleMeshDrawable : public Drawable {
public:
	SingleMeshDrawable(
		Renderer& renderer,
		dx::XMFLOAT3 startPosition,
		dx::XMFLOAT3 startRotation,
		Mesh& mesh,
		std::wstring vertexShaderName,
		std::wstring pixelShaderName,
		std::vector<Color> colors
	);
};

#define MAX_COLORS 10