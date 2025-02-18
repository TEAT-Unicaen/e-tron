#pragma once

#include "../bindable.h"

class VertexBuffer : public Bindable {
public:
	template<class VertexData>
	VertexBuffer(Renderer& renderer, const std::vector<VertexData>& vertices);

	void bind(Renderer& renderer) override;

protected:
	UINT structSize;
	Mwrl::ComPtr<ID3D11Buffer> pVertexBuffer;
};

template<class VertexData>
VertexBuffer::VertexBuffer(Renderer& renderer, const std::vector<VertexData>& vertices)
	: structSize(sizeof(VertexData)) {
	HR_PLUS;

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = this->structSize * static_cast<UINT>(vertices.size());
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0u;
	bufferDesc.MiscFlags = 0u;
	bufferDesc.StructureByteStride = this->structSize;

	D3D11_SUBRESOURCE_DATA subData = {};
	subData.pSysMem = vertices.data();

	CHECK_RENDERER_EXCEPT(this->getDevice(renderer)->CreateBuffer(&bufferDesc, &subData, &this->pVertexBuffer));
}
