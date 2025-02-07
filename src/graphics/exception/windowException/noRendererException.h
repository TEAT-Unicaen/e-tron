#pragma once

#include "../../utils/eTronException.h"

class NoRendererException : public ETronException {
public:
	using ETronException::ETronException;
	const char* getType() const noexcept override {
		return "E-Tron Window Exception [No Renderer found]";
	}
};
#define NO_RENDERER_EXCEPT() NoRendererException(__LINE__, __FILE__)