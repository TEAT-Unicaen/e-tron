#pragma once

#include "constantBuffer.h"

template<typename ConstantData>
class GeometryConstantBuffer : public ConstantBuffer<ConstantData> {
public:
	using ConstantBuffer<ConstantData>::ConstantBuffer;
	void bind(Renderer& renderer) override;
};

template<typename ConstantData>
void GeometryConstantBuffer<ConstantData>::bind(Renderer& renderer) {
	HR_PLUS;
	CHECK_INFO_ONLY_EXCEPT(this->getDeviceContext(renderer)->GSSetConstantBuffers(0u, 1u, this->pConstantBuffer.GetAddressOf()));
}