#include "vertexBuffer.h"

void VertexBuffer::bind(Renderer& renderer) {
	HR_PLUS;
	const UINT offset = 0u;
	CHECK_INFO_ONLY_EXCEPT(this->getDeviceContext(renderer)->IASetVertexBuffers(0u, 1u, this->pVertexBuffer.GetAddressOf(), &this->structSize, &offset));
}