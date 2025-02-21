#include "geometryShader.h"

GeometryShader::GeometryShader(Renderer& renderer, const std::wstring& filename) {
	HR_PLUS;
	std::wstring fullPath = L"shaders/";
	fullPath.append(filename).append(L".cso");
	Mwrl::ComPtr<ID3DBlob> pBlob;
	CHECK_INFO_ONLY_EXCEPT(D3DReadFileToBlob(fullPath.c_str(), &pBlob));
	CHECK_RENDERER_EXCEPT(this->getDevice(renderer)->CreateGeometryShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pGeometryShader));
}

void GeometryShader::bind(Renderer& renderer) {
	HR_PLUS;
	CHECK_INFO_ONLY_EXCEPT(this->getDeviceContext(renderer)->GSSetShader(pGeometryShader.Get(), nullptr, 0u));
}