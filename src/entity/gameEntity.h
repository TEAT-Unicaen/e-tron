#pragma once

#include <string>
#include "../utils/colorEnum.h"

typedef struct SCoords {
	int x;
	int y;
} TCoords;

class GameEntity {
public:
	GameEntity() noexcept;
	GameEntity(std::string name, TCoords coords, ColorE::ColorEnum color) noexcept;
	~GameEntity() = default;

	std::string getName() const noexcept;
	TCoords getCoords() const noexcept;
	ColorE::ColorEnum getColor() const noexcept;
	void setCoords(TCoords coords) noexcept;

    inline operator bool() const noexcept {
		return !name.empty() && color != ColorE::ColorEnum::Undefined && coords.x != -1 && coords.y != -1;
    }

protected:
	std::string name;
	TCoords coords;
	ColorE::ColorEnum color;
};