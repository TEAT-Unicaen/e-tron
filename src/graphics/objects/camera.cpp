#include "camera.h"

Camera::Camera()
	: fov(90.0f), aspectRatio(1.0f), nearZ(0.1f), farZ(1000.0f),
	  position(dx::XMFLOAT3(0.0f, 0.0f, 0.0f)), rotation(dx::XMFLOAT3(0.0f, 0.0f, 0.0f)) {
	updateProjection();
	updateView();
}

void Camera::setFOV(float fov) noexcept {
	this->fov = fov;
	updateProjection();
}

void Camera::setAspectRatio(float aspectRatio) noexcept {
	this->aspectRatio = aspectRatio;
	updateProjection();
}

void Camera::updateFOV(float delatFOV) noexcept {
	this->fov += delatFOV;
	updateProjection();
}

void Camera::setPosition(float x, float y, float z) noexcept {
	this->position = dx::XMFLOAT3(x, y, z);
	updateView();
}

void Camera::setRotation(float x, float y, float z) noexcept {
	this->rotation = dx::XMFLOAT3(x, y, z);
	updateView();
}

void Camera::move(float forward, float right, float up) noexcept {
	const auto pos = dx::XMLoadFloat3(&this->position);

	// Déplacement en fonction de la direction
	const auto moveForward = dx::XMVectorScale(this->lookDirection, forward);
	const auto moveRight = dx::XMVectorScale(this->rightDirection, right);
	const auto moveUp = dx::XMVectorSet(0.0f, up, 0.0f, 0.0f);

	const auto newPos = dx::XMVectorAdd(pos, dx::XMVectorAdd(moveForward, dx::XMVectorAdd(moveRight, moveUp)));

	XMStoreFloat3(&this->position, newPos);
	updateView();
}


void Camera::rotate(float x, float y, float z) noexcept {
	this->rotation.x += x;
	this->rotation.y += y;
	this->rotation.z += z;
	updateView();
}

const dx::XMMATRIX Camera::getProjection() const noexcept {
	return this->projection;
}

const dx::XMMATRIX Camera::getView() const noexcept {
	return this->view;
}

void Camera::updateProjection() noexcept {
	if (this->fov <= 0.0f) this->fov = 1.0f;
	this->projection = dx::XMMatrixPerspectiveFovLH(
		dx::XMConvertToRadians(this->fov),
		this->aspectRatio,
		this->nearZ,
		this->farZ
	);
}

void Camera::updateView() noexcept {
	const auto cameraPosition = dx::XMLoadFloat3(&this->position);
	const auto lookRotation = dx::XMMatrixRotationRollPitchYaw(this->rotation.x, this->rotation.y, this->rotation.z);

	// Vecteurs de base
	const dx::XMVECTOR forwardBaseVector = dx::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const dx::XMVECTOR upBaseVector = dx::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	const dx::XMVECTOR rightBaseVector = dx::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	// Applique la rotation sur les directions
	this->lookDirection = dx::XMVector3Transform(forwardBaseVector, lookRotation);
	this->rightDirection = dx::XMVector3Transform(rightBaseVector, lookRotation);
	const auto upDirection = dx::XMVector3Transform(upBaseVector, lookRotation);

	// Normaliser la direction pour éviter une transformation incorrecte
	this->lookDirection = dx::XMVector3Normalize(lookDirection);
	this->rightDirection = dx::XMVector3Normalize(rightDirection);

	// Calcule le point de visée (cameraTarget)
	const auto cameraTarget = dx::XMVectorAdd(cameraPosition, this->lookDirection);

	// Crée la matrice de vue (LookAtLH)
	this->view = dx::XMMatrixLookAtLH(cameraPosition, cameraTarget, upDirection);
}