#include "drawable.h"

ShaderManager Drawable::shaderManager;

Drawable::Drawable(Renderer& renderer, const dx::XMFLOAT3 startPosition, const dx::XMFLOAT3 startRotation, const dx::XMFLOAT3 scale)
	: position(startPosition), rotation(startRotation), scale(scale), targetPosition(startPosition), targetRotation(startRotation) {}


void Drawable::setPosition(dx::XMFLOAT3 position) noexcept {
	this->position = position;
}

void Drawable::setRotation(dx::XMFLOAT3 rotation) noexcept {
	this->rotation = rotation;
}

void Drawable::setVelocity(dx::XMFLOAT3 velocity) noexcept {
	this->velocity = velocity;
}

void Drawable::setAngularVelocity(dx::XMFLOAT3 angularVelocity) noexcept {
	this->angularVelocity = angularVelocity;
}

void Drawable::setScale(dx::XMFLOAT3 scale) noexcept {
	this->scale = scale;
}

void Drawable::move(dx::XMFLOAT3 translation, float movingTime) noexcept {
	if (movingTime == 0.0f) {
		this->position.x += translation.x;
		this->position.y += translation.y;
		this->position.z += translation.z;
		return;
	}
	this->targetPosition = dx::XMFLOAT3(
		this->position.x + translation.x,
		this->position.y + translation.y,
		this->position.z + translation.z
	);
	this->velocity = dx::XMFLOAT3(
		translation.x / movingTime,
		translation.y / movingTime,
		translation.z / movingTime
	);
}

void Drawable::moveInTo(dx::XMFLOAT3 newPosition, float movingTime) noexcept {
	if (movingTime == 0.0f) {
		this->position = newPosition;
		return;
	}
	this->targetPosition = newPosition;
	this->velocity = dx::XMFLOAT3(
		(newPosition.x - this->position.x) / movingTime,
		(newPosition.y - this->position.y) / movingTime,
		(newPosition.z - this->position.z) / movingTime
	);
}

void Drawable::rotate(dx::XMFLOAT3 rotation, float movingTime) noexcept {
	if (movingTime == 0.0f) {
		this->rotation.x += rotation.x;
		this->rotation.y += rotation.y;
		this->rotation.z += rotation.z;
		return;
	}

	this->targetRotation.x = this->rotation.x + rotation.x;
	this->targetRotation.y = this->rotation.y + rotation.y;
	this->targetRotation.z = this->rotation.z + rotation.z;

	this->angularVelocity.x = rotation.x / movingTime;
	this->angularVelocity.y = rotation.y / movingTime;
	this->angularVelocity.z = rotation.z / movingTime;
}

void Drawable::rotateInTo(dx::XMFLOAT3 newRotation, float movingTime) noexcept {
	if (movingTime == 0.0f) {
		this->rotation = newRotation;
		return;
	}

	this->targetRotation = newRotation;

	this->angularVelocity.x = (newRotation.x - this->rotation.x) / movingTime;
	this->angularVelocity.y = (newRotation.y - this->rotation.y) / movingTime;
	this->angularVelocity.z = (newRotation.z - this->rotation.z) / movingTime;
}

dx::XMMATRIX Drawable::getTransform() const {
	return
		dx::XMMatrixScaling(this->scale.x, this->scale.y, this->scale.z) *
		dx::XMMatrixRotationRollPitchYaw(this->rotation.x, this->rotation.y, this->rotation.z) *
		dx::XMMatrixTranslation(this->position.x, this->position.y, this->position.z);
}

void Drawable::draw(Renderer& renderer) const noexcept(!IS_DEBUG_MODE) {
	this->bindAll(renderer);
	renderer.drawIndexed(this->indexCount);
}

void Drawable::update(float delta) noexcept {
	// Calcul de la distance actuelle (avant déplacement)
	float oldDistanceSq =
		(this->position.x - this->targetPosition.x) * (this->position.x - this->targetPosition.x) +
		(this->position.y - this->targetPosition.y) * (this->position.y - this->targetPosition.y) +
		(this->position.z - this->targetPosition.z) * (this->position.z - this->targetPosition.z);

	// Translation
	this->position.x += this->velocity.x * delta;
	this->position.y += this->velocity.y * delta;
	this->position.z += this->velocity.z * delta;

	// Rotation
	this->rotation.x += this->angularVelocity.x * delta;
	this->rotation.y += this->angularVelocity.y * delta;
	this->rotation.z += this->angularVelocity.z * delta;

	this->rotation.x = fmod(this->rotation.x, dx::XM_2PI);
	this->rotation.y = fmod(this->rotation.y, dx::XM_2PI);
	this->rotation.z = fmod(this->rotation.z, dx::XM_2PI);

	// Nouvelle distance après le déplacement
	float newDistanceSq =
		(this->position.x - this->targetPosition.x) * (this->position.x - this->targetPosition.x) +
		(this->position.y - this->targetPosition.y) * (this->position.y - this->targetPosition.y) +
		(this->position.z - this->targetPosition.z) * (this->position.z - this->targetPosition.z);

	// Si on dépasse la cible, on fixe la position à targetPosition et on stoppe la vitesse
	if (newDistanceSq > oldDistanceSq) {
		this->position = this->targetPosition;
		this->velocity = dx::XMFLOAT3(0.0f, 0.0f, 0.0f);
	}

	// Vérification si la rotation dépasse la cible
	// Si la différence entre la rotation actuelle et la target est plus grande que celle que l'on peut appliquer dans le delta, on arrête la rotation
	if (fabs(this->rotation.x - this->targetRotation.x) < fabs(this->angularVelocity.x) * delta) {
		this->rotation.x = this->targetRotation.x;
		this->angularVelocity.x = 0.0f;
	}

	if (fabs(this->rotation.y - this->targetRotation.y) < fabs(this->angularVelocity.y) * delta) {
		this->rotation.y = this->targetRotation.y;
		this->angularVelocity.y = 0.0f;
	}

	if (fabs(this->rotation.z - this->targetRotation.z) < fabs(this->angularVelocity.z) * delta) {
		this->rotation.z = this->targetRotation.z;
		this->angularVelocity.z = 0.0f;
	}
}

void Drawable::addBindable(std::shared_ptr<Bindable> pBindables) noexcept {
	assert("Use addIndexBuffer for index buffer" && typeid(*pBindables) != typeid(IndexBuffer));
	this->pBindables.push_back(std::move(pBindables));
}

void Drawable::addBindable(std::shared_ptr<IndexBuffer> pIndexBuffer) noexcept(!IS_DEBUG_MODE) {
	assert("Already set the index buffer!" && this->indexCount == 0u);
	this->indexCount = pIndexBuffer.get()->getCount();
	this->pBindables.push_back(std::move(pIndexBuffer));
}

void Drawable::bindAll(Renderer& renderer) const noexcept(!IS_DEBUG_MODE) {
	for (const auto& b : this->pBindables) {
		b->bind(renderer);
	}
}