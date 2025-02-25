#pragma once

#include <DirectXMath.h>

namespace dx = DirectX;

class Camera {
public:
	Camera();
	Camera(const Camera&) = delete;
	~Camera() = default;
	
	void setFOV(float fov) noexcept;
	void setAspectRatio(float aspectRatio) noexcept;

	void updateFOV(float delatFOV) noexcept;

	void setPosition(float x, float y, float z) noexcept;
	void setRotation(float x, float y, float z) noexcept;

	void move(float x, float y, float z) noexcept;
	void rotate(float x, float y, float z) noexcept;

	const dx::XMMATRIX getProjection() const noexcept;
	const dx::XMMATRIX getView() const noexcept;

private:
	void updateProjection() noexcept;
	void updateView() noexcept;

	// Projection
	float fov;
	float aspectRatio;
	float nearZ;
	float farZ;
	dx::XMMATRIX projection;

	// View
	dx::XMFLOAT3 position;
	dx::XMFLOAT3 rotation;
	dx::XMMATRIX view;

	// Direction
	dx::XMVECTOR lookDirection;
	dx::XMVECTOR rightDirection;
};