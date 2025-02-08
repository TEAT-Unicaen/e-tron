#include "rendererHrException.h"

RendererHrException::RendererHrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoDescriptions) noexcept
	: HrException(line, file, hr) {
	for (const auto& m : infoDescriptions) {
		this->infoDescriptions += m;
		this->infoDescriptions.push_back('\n');
	}
	if (!infoDescriptions.empty())
		this->infoDescriptions.pop_back();
}

const char* RendererHrException::what() const noexcept {
	std::ostringstream oss;
	oss << HrException::what() << std::endl;
	if (!infoDescriptions.empty()) {
		oss << "Error Info : " << this->infoDescriptions << std::endl;
	}
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* RendererHrException::getType() const noexcept {
	return "E-Tron Renderer Exception";
}

std::string RendererHrException::getInfoDescription() const noexcept {
	return infoDescriptions;
}

