#pragma once

#include "../bindable.h"

class IndexBuffer : public Bindable {
public:
	IndexBuffer(Renderer& renderer, const std::vector<unsigned short>& indices);
	void bind(Renderer& renderer) override;
	UINT getCount() const;

protected:
	UINT count;
	Mwrl::ComPtr<ID3D11Buffer> pIndexBuffer;
};