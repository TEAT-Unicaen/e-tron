#pragma once

#include <array>

#include "../../core/render/renderer.h"
#include "../bindable/bindable.h"
#include "../bindable/buffers/indexBuffer.h"
#include "../bindable/shaders/shaderManager.h"
#include "../meshes/mesh.h"

namespace dx = DirectX;

class Drawable {
public:
	Drawable() = default;
	Drawable(Renderer& renderer, const dx::XMFLOAT3 startPosition, const dx::XMFLOAT3 startRotation, const dx::XMFLOAT3 scale = dx::XMFLOAT3(1.0f, 1.0f, 1.0f));
	Drawable(const Drawable&) = delete;
	virtual ~Drawable() = default;

	dx::XMFLOAT3 getPosition() const noexcept;

	void setPosition(dx::XMFLOAT3 position) noexcept;
	void setRotation(dx::XMFLOAT3 rotation) noexcept;
	void setVelocity(dx::XMFLOAT3 velocity) noexcept;
	void setAngularVelocity(dx::XMFLOAT3 angularVelocity) noexcept;
	void setScale(dx::XMFLOAT3 scale) noexcept;

	void move(dx::XMFLOAT3 translation, float movingTime) noexcept;
	void moveInTo(dx::XMFLOAT3 newPosition, float movingTime) noexcept;

	void rotate(dx::XMFLOAT3 rotation, float movingTime) noexcept;
	void rotateInTo(dx::XMFLOAT3 newRotation, float movingTime) noexcept;
	
	dx::XMMATRIX getTransform() const;

	virtual void draw(Renderer& renderer) const noexcept(!IS_DEBUG_MODE);
	virtual void update(float delta) noexcept;

	void addBindable(std::shared_ptr<Bindable> pBindables) noexcept(!IS_DEBUG_MODE);
	void addBindable(std::shared_ptr<IndexBuffer> pIndexBuffer) noexcept(!IS_DEBUG_MODE);

	static ShaderManager shaderManager;
	static void loadMesh(const std::string& meshName, const Mesh& mesh);
	static Mesh& getMesh(const std::string& meshName);
protected:
	dx::XMFLOAT3 position = dx::XMFLOAT3(0.0f, 0.0f, 0.0f);
	dx::XMFLOAT3 rotation = dx::XMFLOAT3(0.0f, 0.0f, 0.0f);

	dx::XMFLOAT3 velocity = dx::XMFLOAT3(0.0f, 0.0f, 0.0f);
	dx::XMFLOAT3 angularVelocity = dx::XMFLOAT3(0.0f, 0.0f, 0.0f);

	dx::XMFLOAT3 scale = dx::XMFLOAT3(1.0f, 1.0f, 1.0f);

	dx::XMFLOAT3 targetPosition = dx::XMFLOAT3(0.0f, 0.0f, 0.0f);
	dx::XMFLOAT3 targetRotation = dx::XMFLOAT3(0.0f, 0.0f, 0.0f);
	
	void bindAll(Renderer& renderer) const noexcept(!IS_DEBUG_MODE);
	
	UINT indexCount = 0u;
	std::vector<std::shared_ptr<Bindable>> pBindables;

	static std::unordered_map<std::string, Mesh> meshes;
};