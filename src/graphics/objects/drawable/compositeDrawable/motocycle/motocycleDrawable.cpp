#include "motocycleDrawable.h"

MotocycleDrawable::MotocycleDrawable(Renderer& renderer, dx::XMFLOAT3 position, dx::XMFLOAT3 rotation, Color color)
	: CompositeDrawable(renderer, position, rotation) {

	Mesh wheel = Drawable::getMesh("cylinder");
	std::unique_ptr<Drawable> pWheel1 = std::make_unique<SingleMeshDrawable>(
		renderer,
		dx::XMFLOAT3{ 0.0f, 0.0f, 1.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, dx::XM_PIDIV2},
		wheel,
		L"compositePhongVS",
		L"coloredPhongSpherePS",
		color
	);
	this->addDrawable(std::move(pWheel1));

	std::unique_ptr<Drawable> pWheel2 = std::make_unique<SingleMeshDrawable>(
		renderer,
		dx::XMFLOAT3{ 0.0f, 0.0f, -1.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, dx::XM_PIDIV2 },
		wheel,
		L"compositePhongVS",
		L"coloredPhongSpherePS",
		color
	);
	this->addDrawable(std::move(pWheel2));

	Mesh body = Drawable::getMesh("cube");

	std::unique_ptr<Drawable> pBody = std::make_unique<SingleMeshDrawable>(
		renderer,
		dx::XMFLOAT3{ 0.0f, 0.5f, 0.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		body,
		L"compositePhongVS",
		L"coloredPhongSpherePS",
		color
	);
	pBody->setScale(dx::XMFLOAT3{ 0.5f, 1.0f, 1.0f });
	this->addDrawable(std::move(pBody));


	float scale = 1.0f / 3.0f;
	this->setScale(dx::XMFLOAT3{ scale, scale, scale });
}