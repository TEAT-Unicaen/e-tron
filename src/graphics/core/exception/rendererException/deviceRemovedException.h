#pragma once

#include "rendererHrException.h"

class DeviceRemovedException : public RendererHrException {
	using RendererHrException::RendererHrException;
public:
	const char* getType() const noexcept override {
		return "E-Tron Renderer Exception [Device Removed]";
	}
};