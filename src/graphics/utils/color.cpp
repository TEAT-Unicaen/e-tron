#include "color.h"

dx::XMFLOAT4 Color::toFloat4() const noexcept {
	return dx::XMFLOAT4{this->r, this->g, this->b, this->a};
}

dx::XMFLOAT3 Color::toFloat3() const noexcept {
	return dx::XMFLOAT3{ this->r, this->g, this->b };
}

D2D1::ColorF Color::toD2D1ColorF() const noexcept {
	return D2D1::ColorF(this->r, this->g, this->b, this->a);
}

const Color Color::WHITE = { 1.0f, 1.0f, 1.0f, 1.0f };
const Color Color::BLACK = { 0.0f, 0.0f, 0.0f, 1.0f };

const Color Color::RED = { 1.0f, 0.0f, 0.0f, 1.0f };
const Color Color::GREEN = { 0.0f, 1.0f, 0.0f, 1.0f };
const Color Color::BLUE = { 0.0f, 0.0f, 1.0f, 1.0f };

const Color Color::YELLOW = { 1.0f, 1.0f, 0.0f, 1.0f };
const Color Color::CYAN = { 0.0f, 1.0f, 1.0f, 1.0f };
const Color Color::MAGENTA = { 1.0f, 0.0f, 1.0f, 1.0f };

const Color Color::SILVER = { 0.75f, 0.75f, 0.75f, 1.0f };
const Color Color::GRAY = { 0.5f, 0.5f, 0.5f, 1.0f };