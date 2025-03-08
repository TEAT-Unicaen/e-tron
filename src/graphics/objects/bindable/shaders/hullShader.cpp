#include "hullShader.h"

HullShader::HullShader(Renderer& renderer, const std::wstring& filename) {
	HR_PLUS;
	std::wstring fullPath = L"shaders/";
	fullPath.append(filename).append(L".cso");
	Mwrl::ComPtr<ID3DBlob> pBlob;
	CHECK_INFO_ONLY_EXCEPT(D3DReadFileToBlob(fullPath.c_str(), &pBlob));
	CHECK_RENDERER_EXCEPT(this->getDevice(renderer)->CreateHullShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pHullShader));
}

void HullShader::bind(Renderer& renderer) {
	HR_PLUS;
	CHECK_INFO_ONLY_EXCEPT(this->getDeviceContext(renderer)->HSSetShader(pHullShader.Get(), nullptr, 0u));
}