#pragma once

#include "bindable.h"

class InputLayout : public Bindable {
public:
	InputLayout(Renderer& renderer, const std::vector<D3D11_INPUT_ELEMENT_DESC>& inputElementDesc, ID3DBlob* pVertexShaderBytecode);
	void bind(Renderer& renderer) noexcept override;
protected:
	Mwrl::ComPtr<ID3D11InputLayout> pInputLayout;
};