#include "instanceBuffer.h"

InstanceBuffer::InstanceBuffer(Renderer& renderer, UINT slot, UINT nbInstances)
	: slot(slot),
	count(0u),
	structSize(sizeof(InstanceData)),
	maxInstances(nbInstances) {
	this->instances.resize(nbInstances, InstanceData());
	this->initBuffer(renderer);
}

void InstanceBuffer::initBuffer(Renderer& renderer) {
	HR_PLUS;

	D3D11_BUFFER_DESC instanceBufferDesc = {};
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	instanceBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	instanceBufferDesc.MiscFlags = 0u;
	instanceBufferDesc.ByteWidth = this->structSize * this->maxInstances;
	instanceBufferDesc.StructureByteStride = this->structSize;

	D3D11_SUBRESOURCE_DATA instanceBufferData = {};
	instanceBufferData.pSysMem = this->instances.data();
	CHECK_RENDERER_EXCEPT(this->getDevice(renderer)->CreateBuffer(&instanceBufferDesc, &instanceBufferData, &pInstanceBuffer));
}

void InstanceBuffer::update(Renderer& renderer) noexcept(!IS_DEBUG_MODE) {
	HR_PLUS;
	D3D11_MAPPED_SUBRESOURCE msr;
	CHECK_INFO_ONLY_EXCEPT(this->getDeviceContext(renderer)->Map(pInstanceBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &msr)); // Lock to write
	memcpy(msr.pData, this->instances.data(), this->structSize * this->instances.size());
	this->getDeviceContext(renderer)->Unmap(pInstanceBuffer.Get(), 0u); // Unlock
}

void InstanceBuffer::bind(Renderer& renderer) noexcept(!IS_DEBUG_MODE) {
	HR_PLUS;
	const UINT offset = 0u;
	if (this->needToBeUpdated) {
		this->update(renderer);
		this->needToBeUpdated = false;
	}
	CHECK_INFO_ONLY_EXCEPT(this->getDeviceContext(renderer)->IASetVertexBuffers(this->slot, 1u, this->pInstanceBuffer.GetAddressOf(), &this->structSize, &offset));
}

void InstanceBuffer::addInstance(
	Renderer& renderer,
	const dx::XMFLOAT3 position,
	const dx::XMFLOAT3 rotation,
	const Color& color,
	const dx::XMFLOAT3 scale
) noexcept(!IS_DEBUG_MODE) {
	dx::XMMATRIX transform = dx::XMMatrixScaling(scale.x, scale.y, scale.z) *
		dx::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z) *
		dx::XMMatrixTranslation(position.x, position.y, position.z);
	this->addInstance(renderer, 
		transform,
		color.toFloat4()
	);
}

void InstanceBuffer::addInstance(Renderer& renderer, const dx::FXMMATRIX transform, const dx::XMFLOAT4 color) noexcept(!IS_DEBUG_MODE) {
	if (count >= this->maxInstances)
		this->setMaxInstances(renderer, this->maxInstances * 1.5);
	this->instances[count++] = InstanceData(dx::XMMatrixTranspose(transform), color);
	this->needToBeUpdated = true;		
}

void InstanceBuffer::updateInstance(
	Renderer& renderer,
	UINT i,
	const dx::XMFLOAT3 position,
	const dx::XMFLOAT3 rotation,
	const Color& color,
	const dx::XMFLOAT3 scale
) noexcept(!IS_DEBUG_MODE) {
	dx::XMMATRIX transform = dx::XMMatrixScaling(scale.x, scale.y, scale.z) *
		dx::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z) *
		dx::XMMatrixTranslation(position.x, position.y, position.z);
	this->updateInstance(renderer, i,
		transform,
		color.toFloat4()
	);
}

void InstanceBuffer::updateInstance(Renderer& renderer, UINT i, const dx::FXMMATRIX transform, dx::XMFLOAT4 color) noexcept(!IS_DEBUG_MODE) {
	if (i < count) {
		this->instances[i] = InstanceData(dx::XMMatrixTranspose(transform), color);
		this->needToBeUpdated = true;
	}
}

void InstanceBuffer::updateInstance(Renderer& renderer, UINT i, const Color& color) noexcept(!IS_DEBUG_MODE) {
	if (i < count) {
		this->instances[i].color = color.toFloat4();
		this->needToBeUpdated = true;
	}
}

void InstanceBuffer::clearInstances(Renderer& renderer) noexcept(!IS_DEBUG_MODE) {
	for (UINT i = 0u; i < this->maxInstances; i++)
		this->instances[i] = InstanceData();
	count = 0u;
	this->needToBeUpdated = true;
}

UINT InstanceBuffer::getCount() const noexcept {
	return count;
}

UINT InstanceBuffer::getMaxInstances() const noexcept {
	return maxInstances;
}

void InstanceBuffer::setMaxInstances(Renderer& renderer, UINT maxInstances) noexcept {
	this->maxInstances = maxInstances;
	this->pInstanceBuffer.Reset();
	this->instances.resize(this->maxInstances, InstanceData());
	this->initBuffer(renderer);
}
