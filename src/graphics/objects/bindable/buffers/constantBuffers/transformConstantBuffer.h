#pragma once

#include "../../../drawable/drawable.h"
#include "vertexConstantBuffer.h"

class TransformConstantBuffer : public Bindable {
public:
    TransformConstantBuffer(Renderer& renderer, const Drawable& parent);
    void bind(Renderer& renderer) noexcept override;
private:
	struct TransformBuffer {
		dx::XMMATRIX model;
		dx::XMMATRIX view;
		dx::XMMATRIX projection;
	};
	const TransformBuffer getTransformBuffer(Renderer& renderer) const noexcept;
    VertexConstantBuffer<TransformBuffer> vertexConstantBuffer;
    const Drawable& parent;
};
