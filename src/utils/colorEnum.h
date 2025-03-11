#pragma once

#include <string>
#include <unordered_map>

// RGB struct to hold color values
struct RGB {
	int r, g, b;
};

// Color enum and methods
class Color {
public:
    enum class ColorEnum {
        Red,
        Green,
        Blue,
        Yellow,
        White,
        Orange,
        Purple,
        Cyan,
        Magenta,
        Brown,
        Pink,
        Gray,
        Black,
        Undefined
    };

	using ColorEnum = Color::ColorEnum;

	static std::string getAnsiColor(ColorEnum color) noexcept;
	static std::string printColoredText(ColorEnum color, const std::string& text) noexcept;
	static ColorEnum intToColor(int value);
};

// Hash struct for ColorEnum (necessary for unordered_map)
namespace std {
	template <>
	struct hash<Color::ColorEnum> {
		std::size_t operator()(const Color::ColorEnum& color) const noexcept {
			return std::hash<int>()(static_cast<int>(color));
		}
	};
}