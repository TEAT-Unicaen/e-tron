#pragma once

#include "../bindable.h"

class DomainShader : public Bindable {
public:
	DomainShader(Renderer& renderer, const std::wstring& path);
	void bind(Renderer& renderer) override;
private:
	Mwrl::ComPtr<ID3D11DomainShader> pDomainShader;
};