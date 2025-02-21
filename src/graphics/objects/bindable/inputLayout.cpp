#include "inputLayout.h"

InputLayout::InputLayout(Renderer& renderer, const std::vector<D3D11_INPUT_ELEMENT_DESC>& inputElementDesc, ID3DBlob* pVertexShaderBytecode) {
	HR_PLUS;
	
	CHECK_RENDERER_EXCEPT(this->getDevice(renderer)->CreateInputLayout(
		inputElementDesc.data(),
		(UINT)inputElementDesc.size(),
		pVertexShaderBytecode->GetBufferPointer(),
		pVertexShaderBytecode->GetBufferSize(),
		&(this->pInputLayout)
	));
}

void InputLayout::bind(Renderer& renderer) {
	HR_PLUS;
	CHECK_INFO_ONLY_EXCEPT(this->getDeviceContext(renderer)->IASetInputLayout(this->pInputLayout.Get()));
}