#pragma once

#include "../../bindable.h"

template<typename ConstantData>
class ConstantBuffer : public Bindable {
public:
	ConstantBuffer(Renderer& renderer, UINT slot);
	ConstantBuffer(Renderer& renderer, const ConstantData& constData, UINT slot);
	void update(Renderer& renderer, const ConstantData& constData);
protected:
	Mwrl::ComPtr<ID3D11Buffer> pConstantBuffer;
	UINT slot = 0u;
};

//

template<typename ConstantData>
ConstantBuffer<ConstantData>::ConstantBuffer(Renderer& renderer, UINT slot) 
	: slot(slot) {
	HR_PLUS;
	D3D11_BUFFER_DESC constantBufferDesc = {};
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBufferDesc.MiscFlags = 0u;
	constantBufferDesc.ByteWidth = sizeof(ConstantData);
	constantBufferDesc.StructureByteStride = 0u;
	CHECK_RENDERER_EXCEPT(this->getDevice(renderer)->CreateBuffer(&constantBufferDesc, nullptr, &pConstantBuffer));
}

template<typename ConstantData>
ConstantBuffer<ConstantData>::ConstantBuffer(Renderer& renderer, const ConstantData& constData, UINT slot)
	: slot(slot) {
	HR_PLUS;
	D3D11_BUFFER_DESC constantBufferDesc = {};
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBufferDesc.MiscFlags = 0u;
	constantBufferDesc.ByteWidth = sizeof(constData);
	constantBufferDesc.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA constantBufferData = {};
	constantBufferData.pSysMem = &constData;
	CHECK_RENDERER_EXCEPT(this->getDevice(renderer)->CreateBuffer(&constantBufferDesc, &constantBufferData, &pConstantBuffer));
}

template<typename ConstantData>
void ConstantBuffer<ConstantData>::update(Renderer& renderer, const ConstantData& constData) {
	HR_PLUS;
	D3D11_MAPPED_SUBRESOURCE msr;
	CHECK_INFO_ONLY_EXCEPT(this->getDeviceContext(renderer)->Map(pConstantBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &msr)); // Lock to write
	memcpy(msr.pData, &constData, sizeof(constData));
	this->getDeviceContext(renderer)->Unmap(pConstantBuffer.Get(), 0u); // Unlock
}