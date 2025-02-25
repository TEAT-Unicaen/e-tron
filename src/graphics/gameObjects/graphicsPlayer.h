#pragma once

#include "graphicsGameEntity.h"

class GraphicsPlayer : GraphicsGameEntity {
public:
	GraphicsPlayer() = delete;
	GraphicsPlayer(int id, float x, float y, float z, Color color, Renderer& renderer) noexcept;
	~GraphicsPlayer() = default;

	void createVisual(Renderer& renderer);

	int getId() const noexcept;

	void turnLeft();
	void turnRight();

	void moveForward();

private:
	int id;
	std::unique_ptr<Drawable> cube;
	std::unique_ptr<Drawable> pyramid;
};