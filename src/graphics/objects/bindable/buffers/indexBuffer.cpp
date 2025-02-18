#include "indexBuffer.h"

IndexBuffer::IndexBuffer(Renderer& renderer, const std::vector<unsigned short>& indices) 
	: count((UINT)indices.size()) {
	HR_PLUS;
	D3D11_BUFFER_DESC indexBufferDesc = {};
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.ByteWidth = (UINT)(this->count * sizeof(unsigned short));
	indexBufferDesc.CPUAccessFlags = 0u;
	indexBufferDesc.MiscFlags = 0u;
	indexBufferDesc.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA indexData = {};
	indexData.pSysMem = indices.data();
	CHECK_RENDERER_EXCEPT(this->getDevice(renderer)->CreateBuffer(&indexBufferDesc, &indexData, &pIndexBuffer));
}

void IndexBuffer::bind(Renderer& renderer) {
	HR_PLUS;
	CHECK_INFO_ONLY_EXCEPT(this->getDeviceContext(renderer)->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u));
}

UINT IndexBuffer::getCount() const {
	return this->count;
}