#pragma once

#include "../bindable.h"

class VertexShader : public Bindable {
public:
	VertexShader(Renderer& renderer, const std::wstring& path);
	void bind(Renderer& renderer) override;
	ID3DBlob *getBytecode() const noexcept;
private:
	Mwrl::ComPtr<ID3D11VertexShader> pVertexShader;
	Mwrl::ComPtr<ID3DBlob> pBytecodeBlob;
};