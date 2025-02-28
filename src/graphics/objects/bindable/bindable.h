#pragma once
#include "../../core/renderer.h"

class Bindable {
public:
	virtual void bind(Renderer& renderer) = 0;
	virtual ~Bindable() = default;
protected:
	static ID3D11DeviceContext* getDeviceContext(Renderer& renderer) noexcept;
	static ID3D11Device* getDevice(Renderer& renderer) noexcept;
	static DxgiInfoManager& getInfoManager(Renderer& renderer) noexcept(IS_DEBUG_MODE);
};

#ifndef NDEBUG
	#define HR_PLUS HR; DxgiInfoManager& infoManager = getInfoManager(renderer)
#else
	#define HR_PLUS HR
#endif // !NDEBUG