#pragma once

#include "rendererHrException.h"

class DeviceRemovedException : public RendererHrException {
public:
	DeviceRemovedException(int line, const char* file, HRESULT hr) noexcept
		: RendererHrException(line, file, hr) {}

	const char* getType() const noexcept override {
		return "E-Tron Renderer Exception [Device Removed]";
	}
};
#define DEVICE_REMOVED_EXCEPT(hr) DeviceRemovedException(__LINE__, __FILE__, hr)