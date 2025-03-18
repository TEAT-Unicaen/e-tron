#pragma once

#include <vector>

#include "../bindable.h"

class InstanceBuffer : public Bindable {
public:
	struct InstanceData {
		dx::XMMATRIX transform;
		dx::XMFLOAT4 color;

		InstanceData(const dx::XMMATRIX& transform, const dx::XMFLOAT4& color) noexcept
			: transform(transform), color(color) {}
		InstanceData(const dx::XMMATRIX& transform, const Color& color) noexcept
			: transform(transform), color(color.toFloat4()) {
		}
		InstanceData() noexcept
			: transform(dx::XMMatrixIdentity()), color(Color::WHITE.toFloat4()) {
		}
	};
	InstanceBuffer(Renderer& renderer, UINT slot, UINT nbInstances);

	void update(Renderer& renderer) noexcept(!IS_DEBUG_MODE);
	void bind(Renderer& renderer) noexcept(!IS_DEBUG_MODE) override;

	void addInstance(
		Renderer& renderer,
		const dx::XMFLOAT3 position,
		const dx::XMFLOAT3 rotation,
		const Color& color,
		const dx::XMFLOAT3 scale = dx::XMFLOAT3(1.0f, 1.0f, 1.0f)
	) noexcept(!IS_DEBUG_MODE);
	void addInstance(Renderer& renderer, const dx::FXMMATRIX transform, const dx::XMFLOAT4 color) noexcept(!IS_DEBUG_MODE);

	void updateInstance(
		Renderer& renderer,
		UINT i,
		const dx::XMFLOAT3 position,
		const dx::XMFLOAT3 rotation,
		const Color& color,
		const dx::XMFLOAT3 scale = dx::XMFLOAT3(1.0f, 1.0f, 1.0f)
	) noexcept(!IS_DEBUG_MODE);
	void updateInstance(Renderer& renderer, UINT i, const dx::FXMMATRIX transform, const dx::XMFLOAT4 color) noexcept(!IS_DEBUG_MODE);
	void updateInstance(Renderer& renderer, UINT i, const Color& color) noexcept(!IS_DEBUG_MODE);

	void clearInstances(Renderer& renderer) noexcept(!IS_DEBUG_MODE);

	UINT getCount() const noexcept;

	UINT getMaxInstances() const noexcept;
	void setMaxInstances(Renderer& renderer, UINT maxInstances) noexcept;

private:
	void initBuffer(Renderer& renderer);

	std::vector<InstanceData> instances;
	UINT structSize;
	Mwrl::ComPtr<ID3D11Buffer> pInstanceBuffer;
	UINT slot;

	UINT count;
	UINT maxInstances = 0;

	bool needToBeUpdated = false;
};
