#include "tronException.h"

TronException::TronException(int line, const char* file) noexcept
	: line(line), file(file) {}

const char* TronException::what() const noexcept {
	std::ostringstream oss;
	oss << getType() << std::endl
		<< getLocationInString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* TronException::getType() const noexcept {
	return "Tron Exception";
}

int TronException::getLine() const noexcept {
	return line;
}

const std::string& TronException::getFile() const noexcept {
	return file;
}

std::string TronException::getLocationInString() const noexcept {
	std::ostringstream oss;
	oss << "File: " << file << std::endl
		<< "Line: " << line << std::endl;
	return oss.str();
}