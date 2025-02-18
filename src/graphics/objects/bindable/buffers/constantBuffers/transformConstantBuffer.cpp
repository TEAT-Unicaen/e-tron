#include "transformConstantBuffer.h"

TransformConstantBuffer::TransformConstantBuffer(Renderer& renderer, const Drawable& parent)
	: vertexConstantBuffer(renderer), parent(parent) {}


void TransformConstantBuffer::bind(Renderer& renderer) noexcept {
	// Update the constant buffer with the new transform (for the new frame) and bind it
	this->vertexConstantBuffer.update(renderer, dx::XMMatrixTranspose(
		this->parent.getTransform() * renderer.getProjection()));
	this->vertexConstantBuffer.bind(renderer);
}