#pragma once

#include "../bindable.h"

class HullShader : public Bindable {
public:
	HullShader(Renderer& renderer, const std::wstring& filename);
	void bind(Renderer& renderer) override;
private:
	Mwrl::ComPtr<ID3D11HullShader> pHullShader;
};