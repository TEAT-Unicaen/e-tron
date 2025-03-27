#pragma once
#include "../../bindable.h"

#include <vector>

template<typename StructData>
class StructuredBuffer : public Bindable {
public:
    // Constructors
    StructuredBuffer(Renderer& renderer, const std::vector<StructData>& data, UINT slot);
    StructuredBuffer(Renderer& renderer, UINT elementCount, UINT slot);

    void initBuffers(Renderer& renderer, const std::vector<StructData>& data);
    void update(Renderer& renderer, const std::vector<StructData>& data);


protected:
	UINT elementCount;
	UINT structSize = sizeof(StructData);
    Mwrl::ComPtr<ID3D11Buffer> pStructuredBuffer;
    Mwrl::ComPtr<ID3D11ShaderResourceView> pShaderResourceView;
    UINT slot = 0u;
};

template<typename StructData>
StructuredBuffer<StructData>::StructuredBuffer(Renderer& renderer, const std::vector<StructData>& data, UINT slot)
    :elementCount(data.size()), slot(slot) {
	initBuffers(renderer, data);
}

template<typename StructData>
StructuredBuffer<StructData>::StructuredBuffer(Renderer& renderer, UINT elementCount, UINT slot)
    : elementCount(elementCount), slot(slot) {
	std::vector<StructData> data;
	data.reserve(elementCount);
	initBuffers(renderer, data);
}

template<typename StructData>
void StructuredBuffer<StructData>::initBuffers(Renderer& renderer, const std::vector<StructData>& data) {
    HR_PLUS;

    // Buffer description
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    bufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
    bufferDesc.StructureByteStride = this->structSize;
    bufferDesc.ByteWidth = this->structSize * this->elementCount;

    // Initial data
    D3D11_SUBRESOURCE_DATA initialData = {};
    initialData.pSysMem = data.data();

    // Create buffer
    CHECK_RENDERER_EXCEPT(this->getDevice(renderer)->CreateBuffer(&bufferDesc, &initialData, &pStructuredBuffer));

    // Create Shader Resource View
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = DXGI_FORMAT_UNKNOWN;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
    srvDesc.Buffer.FirstElement = 0;
    srvDesc.Buffer.NumElements = this->elementCount;

    CHECK_RENDERER_EXCEPT(this->getDevice(renderer)->CreateShaderResourceView(pStructuredBuffer.Get(), &srvDesc, &pShaderResourceView));
}

template<typename StructData>
void StructuredBuffer<StructData>::update(Renderer& renderer, const std::vector<StructData>& data) {
    HR_PLUS;
    if (data.size() > elementCount) {
		this->pStructuredBuffer.Reset();
		this->pShaderResourceView.Reset();
		this->elementCount = data.size();
		this->initBuffers(renderer, data);
        return;
    }
    auto* deviceContext = this->getDeviceContext(renderer);

    D3D11_MAPPED_SUBRESOURCE msr;
    CHECK_RENDERER_EXCEPT(deviceContext->Map(pStructuredBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &msr));

    memcpy(msr.pData, data.data(), this->structSize * this->elementCount);

    deviceContext->Unmap(pStructuredBuffer.Get(), 0u);
}