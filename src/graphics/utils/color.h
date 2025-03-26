#pragma once

#include "setUpWindows.h"
#include <DirectXMath.h>
#include <string>
#include <random>

#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")

namespace dx = DirectX;

class Color {
public:
	Color() = delete;
	Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
	Color(UINT r, UINT g, UINT b, UINT a) : r(r / 255.0f), g(g / 255.0f), b(b / 255.0f), a(a / 255.0f) {}

	dx::XMFLOAT4 toFloat4() const noexcept;
	dx::XMFLOAT3 toFloat3() const noexcept;
	D2D1::ColorF toD2D1ColorF() const noexcept;

	std::string toString() const;

	static Color getRandomColor();

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
