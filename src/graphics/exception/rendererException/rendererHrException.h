#pragma once

#include "hrException.h"

class RendererHrException : public HrException {
public:
	RendererHrException(int line, const char* file, HRESULT hr) noexcept
		: HrException(line, file, hr) {}

	const char* getType() const noexcept override {
		return "E-Tron Renderer Exception";
	}
};
#define RENDERER_EXCEPT(hr) RendererHrException(__LINE__, __FILE__, hr)