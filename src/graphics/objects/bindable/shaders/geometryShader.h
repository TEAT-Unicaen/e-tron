#pragma once

#include "../bindable.h"

class GeometryShader : public Bindable {
public:
	GeometryShader(Renderer& renderer, const std::wstring& filename);
	void bind(Renderer& renderer) override;
private:
	Mwrl::ComPtr<ID3D11GeometryShader> pGeometryShader;
};