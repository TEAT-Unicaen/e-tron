#include "instanceBuffer.h"

InstanceBuffer::InstanceBuffer(Renderer& renderer, UINT slot)
	: slot(slot), count(0u), structSize(sizeof(dx::XMMATRIX)) {
	std::vector<dx::XMMATRIX> instances;
	this->initBuffer(renderer, slot, instances);
}

InstanceBuffer::InstanceBuffer(Renderer& renderer, const std::vector<dx::XMMATRIX>& instances, UINT slot)
	: slot(slot), count(static_cast<UINT>(instances.size())), structSize(sizeof(dx::XMMATRIX)) {
	this->initBuffer(renderer, slot, instances);
	for (UINT i = 0u; i < count; i++) {
		this->instances[i] = instances[i];
	}
}

void InstanceBuffer::initBuffer(Renderer& renderer, UINT slot, std::vector<dx::XMMATRIX> instances) {
	instances.reserve(MAX_INSTANCES);
	for (UINT i = this->count; i < MAX_INSTANCES; i++) {
		instances.push_back(dx::XMMatrixIdentity());
	}
	this->instances = instances;

	HR_PLUS;

	D3D11_BUFFER_DESC instanceBufferDesc = {};
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	instanceBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	instanceBufferDesc.MiscFlags = 0u;
	instanceBufferDesc.ByteWidth = this->structSize * MAX_INSTANCES;
	instanceBufferDesc.StructureByteStride = this->structSize;

	D3D11_SUBRESOURCE_DATA instanceBufferData = {};
	instanceBufferData.pSysMem = this->instances.data();
	CHECK_RENDERER_EXCEPT(this->getDevice(renderer)->CreateBuffer(&instanceBufferDesc, &instanceBufferData, &pInstanceBuffer));
}

void InstanceBuffer::update(Renderer& renderer) noexcept(!IS_DEBUG_MODE) {
	HR_PLUS;
	D3D11_MAPPED_SUBRESOURCE msr;
	CHECK_INFO_ONLY_EXCEPT(this->getDeviceContext(renderer)->Map(pInstanceBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &msr)); // Lock to write
	memcpy(msr.pData, this->instances.data(), sizeof(dx::XMMATRIX) * this->instances.size());
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
	const dx::XMFLOAT3 scale
) noexcept(!IS_DEBUG_MODE) {
	if (count < MAX_INSTANCES) {
		instances[count++] = dx::XMMatrixTranspose(
			dx::XMMatrixTranslation(position.x, position.y, position.z) *
			dx::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z) *
			dx::XMMatrixScaling(scale.x, scale.y, scale.z));
	}
	this->needToBeUpdated = true;
}

void InstanceBuffer::addInstance(Renderer& renderer, const dx::XMMATRIX& matrix) noexcept(!IS_DEBUG_MODE) {
	if (count < MAX_INSTANCES)
		instances[count++] = matrix;
}

void InstanceBuffer::updateInstance(
	Renderer& renderer,
	UINT i,
	const dx::XMFLOAT3 position,
	const dx::XMFLOAT3 rotation,
	const dx::XMFLOAT3 scale
) noexcept(!IS_DEBUG_MODE) {
	if (i < count) {
		instances[i] = dx::XMMatrixScaling(scale.x, scale.y, scale.z) *
			dx::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z) *
			dx::XMMatrixTranslation(position.x, position.y, position.z);
	}
	this->needToBeUpdated = true;
}

void InstanceBuffer::updateInstance(Renderer& renderer, UINT i, const dx::XMMATRIX& matrix) noexcept(!IS_DEBUG_MODE) {
	if (i < count) {
		instances[i] = matrix;
	}
	this->needToBeUpdated = true;
}

void InstanceBuffer::removeInstance(Renderer& renderer, UINT i) noexcept(!IS_DEBUG_MODE) {
	if (i < count) {
		instances.erase(instances.begin() + i);
		count--;
	}
	this->needToBeUpdated = true;
}

void InstanceBuffer::clearInstances(Renderer& renderer) noexcept(!IS_DEBUG_MODE) {
	for (UINT i = 0u; i < MAX_INSTANCES; i++) {
		this->instances[0] = dx::XMMatrixIdentity();
	}
	count = 0u;
	this->needToBeUpdated = true;
}

UINT InstanceBuffer::getCount() const noexcept {
	return count;
}
