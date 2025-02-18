#include "bindable.h"

ID3D11DeviceContext* Bindable::getDeviceContext(Renderer& renderer) noexcept {
	return renderer.pDeviceContext.Get();
}

ID3D11Device* Bindable::getDevice(Renderer& renderer) noexcept {
	return renderer.pDevice.Get();
}

DxgiInfoManager& Bindable::getInfoManager(Renderer& renderer) noexcept(!IS_DEBUG_MODE) {
#ifndef NDEBUG
	return renderer.infoManager;
#else
	trow std::logic_error("You can't acces to the infoManager in Release mode (only work on Debug mode).");
#endif // !NDEBUG
}