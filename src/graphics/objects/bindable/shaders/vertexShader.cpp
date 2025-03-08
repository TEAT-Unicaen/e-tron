#include "vertexShader.h"

VertexShader::VertexShader(Renderer& renderer, const std::wstring& filename) {
	HR_PLUS;
	std::wstring fullPath = L"shaders/";
	fullPath.append(filename).append(L".cso");
	CHECK_RENDERER_EXCEPT(D3DReadFileToBlob(fullPath.c_str(), &pBytecodeBlob));
	CHECK_RENDERER_EXCEPT(this->getDevice(renderer)->CreateVertexShader(pBytecodeBlob->GetBufferPointer(), pBytecodeBlob->GetBufferSize(), nullptr, &pVertexShader));
}

void VertexShader::bind(Renderer& renderer) {
	HR_PLUS;
	CHECK_INFO_ONLY_EXCEPT(this->getDeviceContext(renderer)->VSSetShader(pVertexShader.Get(), nullptr, 0u));
}

ID3DBlob *VertexShader::getBytecode() const noexcept {
	return pBytecodeBlob.Get();
}