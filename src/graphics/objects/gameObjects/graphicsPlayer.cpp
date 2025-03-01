#include "graphicsPlayer.h"

GraphicsPlayer::GraphicsPlayer(int id, float x, float y, float z, Color color, Renderer& renderer) noexcept
	: GraphicsGameEntity(x, y, z, color), id(id) {
	createVisual(renderer);
}

int GraphicsPlayer::getId() const noexcept {
	return id;
}

void GraphicsPlayer::createVisual(Renderer& renderer) {
	std::array<Color, 5> color5 = {
		this->color, this->color, this->color, this->color, this->color
	};
	std::array<Color, 6> color6 = {
		this->color, this->color, this->color, this->color, this->color, this->color
	};
	this->cube = std::make_unique<ColoredCube>(
		renderer,
		dx::XMFLOAT3{ this->x - 0.5f, this->y, this->z },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		color6
	);
	this->pyramid = std::make_unique<ColoredSquarePyramid>(
		renderer,
		dx::XMFLOAT3{ this->x + 0.5f, this->y, this->z },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		color5
	);
}

void GraphicsPlayer::turnLeft() {
	// TODO
}

void GraphicsPlayer::turnRight() {
	// TODO
}

void GraphicsPlayer::moveForward() {
	// TODO
}