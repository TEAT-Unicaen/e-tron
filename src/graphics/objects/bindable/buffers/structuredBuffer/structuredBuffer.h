#pragma once
#include "../../bindable.h"

#include <vector>

template<typename StructData>
class StructuredBuffer : public Bindable {
public:
    // Constructors
    StructuredBuffer(Renderer& renderer, const std::vector<StructData>& data, UINT slot);
    StructuredBuffer(Renderer& renderer, UINT elementCount, UINT slot);

    // Update method to modify buffer contents
    void update(Renderer& renderer, const std::vector<StructData>& data);

protected:
    Mwrl::ComPtr<ID3D11Buffer> pStructuredBuffer;
    Mwrl::ComPtr<ID3D11ShaderResourceView> pShaderResourceView;
    UINT slot = 0u;
};

template<typename StructData>
StructuredBuffer<StructData>::StructuredBuffer(Renderer& renderer, const std::vector<StructData>& data, UINT slot)
    : slot(slot) {
    HR_PLUS;

    // Buffer description
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    bufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
    bufferDesc.StructureByteStride = sizeof(StructData);
    bufferDesc.ByteWidth = sizeof(StructData) * static_cast<UINT>(data.size());

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
    srvDesc.Buffer.NumElements = static_cast<UINT>(data.size());

    CHECK_RENDERER_EXCEPT(this->getDevice(renderer)->CreateShaderResourceView(pStructuredBuffer.Get(), &srvDesc, &pShaderResourceView));
}

template<typename StructData>
StructuredBuffer<StructData>::StructuredBuffer(Renderer& renderer, UINT elementCount, UINT slot)
    : slot(slot) {
    HR_PLUS;

    // Buffer description
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    bufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
    bufferDesc.StructureByteStride = sizeof(StructData);
    bufferDesc.ByteWidth = sizeof(StructData) * elementCount;

    // Create buffer
    CHECK_RENDERER_EXCEPT(this->getDevice(renderer)->CreateBuffer(&bufferDesc, nullptr, &pStructuredBuffer));

    // Create Shader Resource View
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = DXGI_FORMAT_UNKNOWN;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
    srvDesc.Buffer.FirstElement = 0;
    srvDesc.Buffer.NumElements = elementCount;

    CHECK_RENDERER_EXCEPT(this->getDevice(renderer)->CreateShaderResourceView(pStructuredBuffer.Get(), &srvDesc, &pShaderResourceView));
}

template<typename StructData>
void StructuredBuffer<StructData>::update(Renderer& renderer, const std::vector<StructData>& data) {
    HR_PLUS;

    auto* deviceContext = this->getDeviceContext(renderer);

    D3D11_MAPPED_SUBRESOURCE msr;
    CHECK_RENDERER_EXCEPT(deviceContext->Map(pStructuredBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &msr));

    memcpy(msr.pData, data.data(), sizeof(StructData) * data.size());

    deviceContext->Unmap(pStructuredBuffer.Get(), 0u);
}