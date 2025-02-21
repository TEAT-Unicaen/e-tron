#pragma once

#include "material.h"
#include "../../color.h"

#include <vector>

class ColorMaterial : public Material {
public:
	ColorMaterial(Color color);
	ColorMaterial(std::vector<Color> colors);

	std::vector<Color> getColors() const noexcept;
private:
	std::vector<Color> colors;
};