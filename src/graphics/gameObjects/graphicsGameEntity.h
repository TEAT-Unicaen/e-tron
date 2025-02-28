#pragma once 

#include "../utils/color.h"
#include "../objects/objects.h"
#include "../core/window.h"
#include <memory>

class GraphicsGameEntity {
public:
	GraphicsGameEntity() = delete;
	GraphicsGameEntity(float x, float y, float z, Color color) noexcept;
	GraphicsGameEntity(const GraphicsGameEntity&) = delete;
	~GraphicsGameEntity() = default;

	dx::XMFLOAT3 getCoords() const noexcept;
	Color getColor() const noexcept;
	void setCoords(float x, float y, float z) noexcept;

	void removeVisual();

protected:
	float x;
	float y;
	float z;
	Color color;
};