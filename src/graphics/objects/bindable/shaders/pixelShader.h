#pragma once

#include "../bindable.h"

class PixelShader : public Bindable {
public:
	PixelShader(Renderer& renderer, const std::wstring& filename);
	void bind(Renderer& renderer) override;
private:
	Mwrl::ComPtr<ID3D11PixelShader> pPixelShader;
};