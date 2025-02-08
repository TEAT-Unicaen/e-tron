#pragma once

#include "../hrException.h"

#include <vector>

class RendererHrException : public HrException {
public:
	RendererHrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoDescriptions = {}) noexcept;

	const char* what() const noexcept override;

	const char* getType() const noexcept override;

	std::string getInfoDescription() const noexcept;
private:
	std::string infoDescriptions;
};
#define RENDERER_EXCEPT_NO_INFO(hr) RendererHrException(__LINE__, __FILE__, hr)
#define RENDERER_LAST_EXCEPT_NO_INFO() RENDERER_EXCEPT_NO_INFO(GetLastError())

#define CHECK_RENDERER_EXCEPT_NO_INFO(hrcall) if (FAILED(hr = (hrcall))) throw RENDERER_EXCEPT_NO_INFO(hr)