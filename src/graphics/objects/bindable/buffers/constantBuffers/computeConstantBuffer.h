#pragma once

#include "constantBuffer.h"

template<typename ConstantData>
class ComputeConstantBuffer : public ConstantBuffer<ConstantData> {
public:
	using ConstantBuffer<ConstantData>::ConstantBuffer;
	void bind(Renderer& renderer) override;
};

//

template<typename ConstantData>
void ComputeConstantBuffer<ConstantData>::bind(Renderer& renderer) {
	HR_PLUS;
	CHECK_INFO_ONLY_EXCEPT(this->getDeviceContext(renderer)->CSSetConstantBuffers(this->slot, 1u, this->pConstantBuffer.GetAddressOf()));
}