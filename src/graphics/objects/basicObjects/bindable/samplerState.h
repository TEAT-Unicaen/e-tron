#pragma once

#include "bindable.h"

class SamplerState : public Bindable {
public:
	SamplerState(Renderer& renderer, BOOL isPixelArt = 0);
	void bind(Renderer& renderer) override;
protected:
	Mwrl::ComPtr<ID3D11SamplerState> pSamplerState;
};