#pragma once

#include <string>

typedef struct SCoords {
	int x;
	int y;
} TCoords;

class GameEntity {
public:
	GameEntity() noexcept;
	GameEntity(std::string name, TCoords coords, int color) noexcept;
	~GameEntity() = default;

	std::string getName() const noexcept;
	TCoords getCoords() const noexcept;
	int getColor() const noexcept;
	void setCoords(TCoords coords) noexcept;

	inline operator bool() const noexcept {
		return !name.empty() || color != -1 || (coords.x != -1 || coords.y != -1);
	}

protected:
	std::string name;
	TCoords coords;
	int color;
};