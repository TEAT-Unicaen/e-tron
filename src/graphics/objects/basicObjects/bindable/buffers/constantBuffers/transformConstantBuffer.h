#pragma once

#include <DirectXMath.h>
#include "../../../drawable.h"
#include "vertexConstantBuffer.h"

class TransformConstantBuffer : public Bindable {
public:
    TransformConstantBuffer(Renderer& renderer, const Drawable& parent);
    void bind(Renderer& renderer) noexcept override;
private:
    VertexConstantBuffer<dx::XMMATRIX> vertexConstantBuffer;
    const Drawable& parent;
};
