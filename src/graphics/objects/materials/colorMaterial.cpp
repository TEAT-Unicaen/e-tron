#include "colorMaterial.h"

ColorMaterial::ColorMaterial(Color color)
	: Material(Material::Type::COLOR), colors({ color }) {
}

ColorMaterial::ColorMaterial(std::vector<Color> colors)
	: Material(Material::Type::COLOR), colors(colors) {
}

std::vector<Color> ColorMaterial::getColors() const noexcept {
	return this->colors;
}