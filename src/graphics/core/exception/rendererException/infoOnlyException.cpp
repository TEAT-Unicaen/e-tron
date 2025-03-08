#include "infoOnlyException.h"

InfoOnlyException::InfoOnlyException(int line, const char* file, std::vector<std::string> infoDescriptions) noexcept
	: ETronException(line, file) {
		for (const auto& m : infoDescriptions) {
			this->infoDescriptions += m;
			this->infoDescriptions.push_back('\n');
		}
		if (!infoDescriptions.empty())
			this->infoDescriptions.pop_back();
	}

const char* InfoOnlyException::what() const noexcept {
	std::ostringstream oss;
	oss << this->getType() << std::endl
		<< "\n[Error Info :\n" << this->getInfoDescription() << std::endl << std::endl;
	oss << this->getLocationInString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* InfoOnlyException::getType() const noexcept {
	return "E-Tron Renderer Info Exception";
}

std::string InfoOnlyException::getInfoDescription() const noexcept {
	return infoDescriptions;
}