#include "pixelShader.h"

PixelShader::PixelShader(Renderer& renderer, const std::wstring& filename) {
	HR_PLUS;
	std::wstring fullPath = L"shaders/";
	fullPath.append(filename).append(L".cso");
	Mwrl::ComPtr<ID3DBlob> pBlob;
	CHECK_INFO_ONLY_EXCEPT(D3DReadFileToBlob(fullPath.c_str(), &pBlob));
	CHECK_RENDERER_EXCEPT(this->getDevice(renderer)->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader));
}

void PixelShader::bind(Renderer& renderer) {
	HR_PLUS;
	CHECK_INFO_ONLY_EXCEPT(this->getDeviceContext(renderer)->PSSetShader(pPixelShader.Get(), nullptr, 0u));
}