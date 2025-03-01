#pragma once

#include "bindable.h"

class Topology : public Bindable {
public:
	Topology(Renderer& renderer, D3D11_PRIMITIVE_TOPOLOGY type);
	void bind(Renderer& renderer) override;
protected:
	D3D11_PRIMITIVE_TOPOLOGY type;
};