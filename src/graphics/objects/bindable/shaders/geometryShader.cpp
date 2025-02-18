#include "geometryShader.h"

GeometryShader::GeometryShader(Renderer& renderer, const std::wstring& path) {
	HR_PLUS;
	Mwrl::ComPtr<ID3DBlob> pBlob;
	CHECK_INFO_ONLY_EXCEPT(D3DReadFileToBlob(path.c_str(), &pBlob));
	CHECK_RENDERER_EXCEPT(this->getDevice(renderer)->CreateGeometryShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pGeometryShader));
}

void GeometryShader::bind(Renderer& renderer) {
	HR_PLUS;
	CHECK_INFO_ONLY_EXCEPT(this->getDeviceContext(renderer)->GSSetShader(pGeometryShader.Get(), nullptr, 0u));
}