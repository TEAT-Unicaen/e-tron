#pragma once
#include "structuredBuffer.h"

template<typename StructData>
class GeometryStructuredBuffer : public StructuredBuffer<StructData> {
public:
	using StructuredBuffer<StructData>::StructuredBuffer;
	void bind(Renderer& renderer) override;
};

template<typename StructData>
void GeometryStructuredBuffer<StructData>::bind(Renderer& renderer) {
    HR_PLUS;
    CHECK_INFO_ONLY_EXCEPT(this->getDeviceContext(renderer)->GSSetShaderResources(this->slot, 1u, this->pShaderResourceView.GetAddressOf()));
}