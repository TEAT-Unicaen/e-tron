#include "transformConstantBuffer.h"

TransformConstantBuffer::TransformConstantBuffer(Renderer& renderer, const Drawable& parent)
	: vertexConstantBuffer(renderer, 0u), parent(parent) {}

void TransformConstantBuffer::bind(Renderer& renderer) noexcept {
	// Update the constant buffer with the new transform (for the new frame) and bind it

	this->vertexConstantBuffer.update(renderer, this->getTransformBuffer(renderer));
	this->vertexConstantBuffer.bind(renderer);
}

const TransformConstantBuffer::TransformBuffer TransformConstantBuffer::getTransformBuffer(Renderer& renderer) const noexcept {
	auto model = this->parent.getTransform();
	auto modelView = model * renderer.getView();
	auto modelViewProj = modelView * renderer.getProjection();
	return {
		dx::XMMatrixTranspose(model),
		dx::XMMatrixTranspose(modelView),
		dx::XMMatrixTranspose(modelViewProj)
	};
}