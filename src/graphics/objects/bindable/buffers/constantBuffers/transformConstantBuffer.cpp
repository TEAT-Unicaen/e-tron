#include "transformConstantBuffer.h"

TransformConstantBuffer::TransformConstantBuffer(Renderer& renderer, const Drawable& parent)
	: vertexConstantBuffer(renderer, 0u), parent(parent) {}

void TransformConstantBuffer::bind(Renderer& renderer) noexcept {
	// Update the constant buffer with the new transform (for the new frame) and bind it

	this->vertexConstantBuffer.update(renderer, this->getTransformBuffer(renderer));
	this->vertexConstantBuffer.bind(renderer);
}

const TransformConstantBuffer::TransformBuffer TransformConstantBuffer::getTransformBuffer(Renderer& renderer) const noexcept {
	return {
		dx::XMMatrixTranspose(this->parent.getTransform()),
		dx::XMMatrixTranspose(renderer.getView()),
		dx::XMMatrixTranspose(renderer.getProjection())
	};
}