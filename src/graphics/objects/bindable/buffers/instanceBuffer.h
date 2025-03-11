#pragma once

#include <vector>

#include "../bindable.h"

class InstanceBuffer : public Bindable {
public:
	InstanceBuffer(Renderer& renderer, UINT slot);
	InstanceBuffer(Renderer& renderer, const std::vector<dx::XMMATRIX>& matrices, UINT slot);

	void update(Renderer& renderer) noexcept(!IS_DEBUG_MODE);
	void bind(Renderer& renderer) noexcept(!IS_DEBUG_MODE) override;

	void addInstance(
		Renderer& renderer,
		const dx::XMFLOAT3 position,
		const dx::XMFLOAT3 rotation,
		const dx::XMFLOAT3 scale = dx::XMFLOAT3(1.0f, 1.0f, 1.0f)
	) noexcept(!IS_DEBUG_MODE);
	void addInstance(Renderer& renderer, const dx::XMMATRIX& matrix) noexcept(!IS_DEBUG_MODE);

	void updateInstance(Renderer& renderer, UINT i, const dx::XMFLOAT3 position, const dx::XMFLOAT3 rotation, const dx::XMFLOAT3 scale = dx::XMFLOAT3(1.0f, 1.0f, 1.0f)) noexcept(!IS_DEBUG_MODE);
	void updateInstance(Renderer& renderer, UINT i, const dx::XMMATRIX& matrix) noexcept(!IS_DEBUG_MODE);

	void removeInstance(Renderer& renderer, UINT i) noexcept(!IS_DEBUG_MODE);
	void clearInstances(Renderer& renderer) noexcept(!IS_DEBUG_MODE);

	UINT getCount() const noexcept;
private:
	void initBuffer(Renderer& renderer, UINT slot, std::vector<dx::XMMATRIX> instances);

	std::vector<dx::XMMATRIX> instances;
	Mwrl::ComPtr<ID3D11Buffer> pInstanceBuffer;
	UINT slot;
	UINT count;
	UINT structSize;

	bool needToBeUpdated = false;
};

#define MAX_INSTANCES 100000u // 10_000