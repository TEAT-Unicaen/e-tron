#pragma once

#include <string>
#include <unordered_map>

// RGB struct to hold color values
struct RGB {
	int r, g, b;
};

// Color enum and methods
class ColorE {
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

	using ColorEnum = ColorE::ColorEnum;

	static std::string getAnsiColor(ColorEnum color) noexcept;
	static std::string printColoredText(ColorEnum color, const std::string& text) noexcept;
	static ColorEnum intToColor(int value);
};

// Hash struct for ColorEnum (necessary for unordered_map)
namespace std {
	template <>
	struct hash<ColorE::ColorEnum> {
		std::size_t operator()(const ColorE::ColorEnum& color) const noexcept {
			return std::hash<int>()(static_cast<int>(color));
		}
	};
}