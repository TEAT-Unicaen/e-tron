#include "colorEnum.h"
#include <iostream>

std::unordered_map<Color::ColorEnum, RGB> colorMap = {
    {Color::ColorEnum::Red, {255, 0, 0}},
    {Color::ColorEnum::Green, {0, 255, 0}},
    {Color::ColorEnum::Blue, {0, 0, 255}},
    {Color::ColorEnum::Yellow, {255, 255, 0}},
    {Color::ColorEnum::Black, {0, 0, 0}},
    {Color::ColorEnum::White, {255, 255, 255}},
    {Color::ColorEnum::Orange, {255, 165, 0}},
    {Color::ColorEnum::Purple, {128, 0, 128}},
    {Color::ColorEnum::Cyan, {0, 255, 255}},
    {Color::ColorEnum::Magenta, {255, 0, 255}}
};

std::string Color::getAnsiColor(ColorEnum color) noexcept {
	switch (color) {
		case ColorEnum::Red:
			return "\033[31m";
		case ColorEnum::Green:
			return "\033[32m";
		case ColorEnum::Blue:
			return "\033[34m";
		case ColorEnum::Yellow:
			return "\033[33m";
		case ColorEnum::Black:
			return "\033[30m";
		case ColorEnum::White:
			return "\033[37m";
		case ColorEnum::Orange:
			return "\033[38;5;208m";
		case ColorEnum::Purple:
			return "\033[38;5;57m";
		case ColorEnum::Cyan:
			return "\033[36m";
		case ColorEnum::Magenta:
			return "\033[35m";
		default:
			return "\033[0m";
	};
}

std::string Color::printColoredText(ColorEnum color, const std::string& text) noexcept {
	return getAnsiColor(color) + text + "\033[0m";
}

RGB Color::getColorRGB(ColorEnum color) noexcept {
	return colorMap[color];
}

Color::ColorEnum Color::intToColor(int value) {
	if (value >= 0 && value <= static_cast<int>(Color::ColorEnum::Magenta)) {
		return static_cast<Color::ColorEnum>(value);
	}
	throw std::out_of_range("Invalid color index");
}
