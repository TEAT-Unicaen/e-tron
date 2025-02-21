#pragma once

class Material {
public:
	enum class Type {
		NONE,
		COLOR,
		TEXTURE
	};
	Material() = delete;
	Material(Material::Type type);

	Material::Type getType() const noexcept;

private:
	Material::Type type = Material::Type::NONE;
};