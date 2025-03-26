#pragma once
#include "structuredBuffer.h"

template<typename StructData>
class DomainStructuredBuffer : public StructuredBuffer<StructData> {
public:
	using StructuredBuffer<StructData>::StructuredBuffer;
	void bind(Renderer& renderer) override;
};

template<typename StructData>
void DomainStructuredBuffer<StructData>::bind(Renderer& renderer) {
    HR_PLUS;
    CHECK_INFO_ONLY_EXCEPT(this->getDeviceContext(renderer)->DSSetShaderResources(this->slot, 1u, this->pShaderResourceView.GetAddressOf()));
}