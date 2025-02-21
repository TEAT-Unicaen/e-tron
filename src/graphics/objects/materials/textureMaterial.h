#pragma once

#include "material.h"
#include "../../image.h"

class TextureMaterial : public Material {
public:
	TextureMaterial(std::wstring path);

	const std::wstring &getPath() const noexcept;
	Image *getImage() const noexcept;

private:
	std::wstring path;
	std::unique_ptr<Image> image;
};