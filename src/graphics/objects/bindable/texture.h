#pragma once

#include "bindable.h"
#include "../../utils/image.h"

class Texture : public Bindable {
public:
	Texture(Renderer& renderer, const Image& image);
	void bind(Renderer& renderer) override;
protected:
	Mwrl::ComPtr<ID3D11ShaderResourceView> pTextureView;
};