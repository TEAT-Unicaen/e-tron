#include "etronException.h"

ETronException::ETronException(int line, const char* file) noexcept
	: line(line), file(file) {}

ETronException::ETronException(int line, const char* file, const char* message) noexcept
	: line(line), file(file), message(message) {}

const char* ETronException::what() const noexcept {
	std::ostringstream oss;
	oss << getType() << std::endl
		<< message << std::endl
		<< getLocationInString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* ETronException::getType() const noexcept {
	return "E-Tron Exception";
}

int ETronException::getLine() const noexcept {
	return line;
}

const std::string& ETronException::getFile() const noexcept {
	return file;
}

std::string ETronException::getLocationInString() const noexcept {
	std::ostringstream oss;
	oss << "File: " << file << std::endl
		<< "Line: " << line << std::endl;
	return oss.str();
}