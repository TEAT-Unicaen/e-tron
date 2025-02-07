#pragma once

#include "hrException.h"

class WindowHrException : public HrException {
public:
	WindowHrException(int line, const char* file, HRESULT hr) noexcept
		: HrException(line, file, hr) {}

	const char* getType() const noexcept override {
		return "E-Tron Window Exception";
	}
};
#define WINDOW_EXCEPT(hr) WindowHrException(__LINE__, __FILE__, hr)