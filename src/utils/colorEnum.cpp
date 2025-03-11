#include "colorEnum.h"
#include <iostream>

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
		case ColorEnum::Brown:
			return "\033[38;5;130m";
		case ColorEnum::Pink:
			return "\033[38;5;198m";
		case ColorEnum::Gray:
			return "\033[38;5;245m";
		default:
			return "\033[0m";
	};
}

std::string Color::printColoredText(ColorEnum color, const std::string& text) noexcept {
	return getAnsiColor(color) + text + "\033[0m";
}

Color::ColorEnum Color::intToColor(int value) {
	// Cap the value to 12 and reset to 0 if over
	value = value % 12;
	if (value >= 0 && value <= static_cast<int>(Color::ColorEnum::Gray)) {
		return static_cast<Color::ColorEnum>(value);
	}
	throw std::out_of_range("Invalid color index");
}
