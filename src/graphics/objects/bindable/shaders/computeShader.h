#pragma once

#include "../bindable.h"

class ComputeShader : public Bindable {
public:
	ComputeShader(Renderer& renderer, const std::wstring& filename);
	void bind(Renderer& renderer) override;
private:
	Mwrl::ComPtr<ID3D11ComputeShader> pComputeShader;
};