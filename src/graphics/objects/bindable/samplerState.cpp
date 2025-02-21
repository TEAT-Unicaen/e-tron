#include "samplerState.h"

SamplerState::SamplerState(Renderer& renderer, BOOL isPixelArt) {
	HR_PLUS;
	// Create the sampler state
	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = isPixelArt ? D3D11_FILTER_MIN_MAG_MIP_POINT : D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	CHECK_RENDERER_EXCEPT(this->getDevice(renderer)->CreateSamplerState(
		&samplerDesc,
		&this->pSamplerState
	));
}

void SamplerState::bind(Renderer& renderer) {
	HR_PLUS;
	CHECK_INFO_ONLY_EXCEPT(this->getDeviceContext(renderer)->PSSetSamplers(0u, 1u, this->pSamplerState.GetAddressOf()));
}