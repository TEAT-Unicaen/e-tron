#include "textureMaterial.h"

TextureMaterial::TextureMaterial(std::wstring path)
	: Material(Material::Type::TEXTURE), path(path), image(std::make_unique<Image>(path)) {}

const std::wstring &TextureMaterial::getPath() const noexcept {
	return this->path;
}

Image *TextureMaterial::getImage() const noexcept {
	return this->image.get();
}