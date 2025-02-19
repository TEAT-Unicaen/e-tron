#pragma once

#include "setUpWindows.h"
#include <DirectXMath.h>

namespace dx = DirectX;

class Color {
public:
	Color() = delete;
	Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
	Color(UINT r, UINT g, UINT b, UINT a) : r(r / 255.0f), g(g / 255.0f), b(b / 255.0f), a(a / 255.0f) {}

	dx::XMFLOAT4 getDx() const {
		return { this->r, this->g, this->b, this->a };
	}

	// Default colors
	static const Color WHITE;
	static const Color BLACK;

	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;

	static const Color YELLOW;
	static const Color CYAN;
	static const Color MAGENTA;

	static const Color SILVER;
	static const Color GRAY;

	float r;
	float g;
	float b;
	float a;
};
