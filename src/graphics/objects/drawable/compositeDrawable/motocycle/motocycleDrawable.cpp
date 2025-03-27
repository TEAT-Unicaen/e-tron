#include "motocycleDrawable.h"

MotocycleDrawable::MotocycleDrawable(Renderer& renderer, dx::XMFLOAT3 position, dx::XMFLOAT3 rotation, Color playerColor, Color baseColor)
	: CompositeDrawable(renderer, position, rotation) {

	// WHEELS
	Mesh Innerwheel = Drawable::getMesh("Innerwheel");
	Mesh Outerwheel = Drawable::getMesh("Outerwheel");
	std::unique_ptr<Drawable> pInnerWheel1 = std::make_unique<SingleMeshDrawable>(
		renderer,
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.9f },
		dx::XMFLOAT3{ 0.0f, 0.0f, dx::XM_PIDIV2},
		Innerwheel,
		L"compositePhongVS",
		L"coloredPhongSpherePS",
		playerColor
	);
	std::unique_ptr<Drawable> pOuterWheel1 = std::make_unique<SingleMeshDrawable>(
		renderer,
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.9f },
		dx::XMFLOAT3{ 0.0f, 0.0f, dx::XM_PIDIV2 },
		Outerwheel,
		L"compositePhongVS",
		L"coloredPhongSpherePS",
		baseColor
	);
	this->addDrawable(std::move(pInnerWheel1));
	this->addDrawable(std::move(pOuterWheel1));

	std::unique_ptr<Drawable> pInnerWheel2 = std::make_unique<SingleMeshDrawable>(
		renderer,
		dx::XMFLOAT3{ 0.0f, 0.0f, -0.9f },
		dx::XMFLOAT3{ 0.0f, 0.0f, dx::XM_PIDIV2 },
		Innerwheel,
		L"compositePhongVS",
		L"coloredPhongSpherePS",
		playerColor
	);
	std::unique_ptr<Drawable> pOuterWheel2 = std::make_unique<SingleMeshDrawable>(
		renderer,
		dx::XMFLOAT3{ 0.0f, 0.0f, -0.9f },
		dx::XMFLOAT3{ 0.0f, 0.0f, dx::XM_PIDIV2 },
		Outerwheel,
		L"compositePhongVS",
		L"coloredPhongSpherePS",
		baseColor
	);
	this->addDrawable(std::move(pInnerWheel2));
	this->addDrawable(std::move(pOuterWheel2));

	// BODY
	Mesh body = Drawable::getMesh("cube");
	std::unique_ptr<Drawable> pInnerbase = std::make_unique<SingleMeshDrawable>(
		renderer,
		dx::XMFLOAT3{ 0.0f, 0.0f, -0.2f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		body,
		L"compositePhongVS",
		L"coloredPhongSpherePS",
		baseColor
	);
	std::unique_ptr<Drawable> pOuterbase = std::make_unique<SingleMeshDrawable>(
		renderer,
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		body,
		L"compositePhongVS",
		L"coloredPhongSpherePS",
		playerColor
	);
	std::unique_ptr<Drawable> pUpperbase = std::make_unique<SingleMeshDrawable>(
		renderer,
		dx::XMFLOAT3{ 0.0f, 0.4f, 0.2f },
		dx::XMFLOAT3{ 4.0f, 0.0f, 0.0f },
		body,
		L"compositePhongVS",
		L"coloredPhongSpherePS",
		baseColor
	);
	std::unique_ptr<Drawable> pTopbase = std::make_unique<SingleMeshDrawable>(
		renderer,
		dx::XMFLOAT3{ 0.0f, 0.82f, 0.67f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		body,
		L"compositePhongVS",
		L"coloredPhongSpherePS",
		baseColor
	);
	pInnerbase->setScale(dx::XMFLOAT3{ 0.35f, 0.5f, 0.9f });
	pOuterbase->setScale(dx::XMFLOAT3{ 0.45f, 0.3f, 0.3f });
	pUpperbase->setScale(dx::XMFLOAT3{ 0.30f, 1.4f, 0.50f });
	pTopbase->setScale(dx::XMFLOAT3{ 0.30f, 0.4f, 0.4f });
	this->addDrawable(std::move(pInnerbase));
	this->addDrawable(std::move(pOuterbase));
	this->addDrawable(std::move(pUpperbase));
	this->addDrawable(std::move(pTopbase));

	// TUBE
	Mesh tube = Drawable::getMesh("tube");
	std::unique_ptr<Drawable> pFrontLeft = std::make_unique<SingleMeshDrawable>(
		renderer,
		dx::XMFLOAT3{ -0.2f, 0.65f, 0.75f },
		dx::XMFLOAT3{ 2.75f, 0.0f, 0.0f },
		tube,
		L"compositePhongVS",
		L"coloredPhongSpherePS",
		playerColor
	);
	std::unique_ptr<Drawable> pFrontRight = std::make_unique<SingleMeshDrawable>(
		renderer,
		dx::XMFLOAT3{ 0.2f, 0.65f, 0.75f },
		dx::XMFLOAT3{ 2.75f, 0.0f, 0.0f },
		tube,
		L"compositePhongVS",
		L"coloredPhongSpherePS",
		playerColor
	);
	std::unique_ptr<Drawable> pBackLeft = std::make_unique<SingleMeshDrawable>(
		renderer,
		dx::XMFLOAT3{ -0.2f, 0.0f, -0.3f },
		dx::XMFLOAT3{ dx::XM_PIDIV2, 0.0f, 0.0f },
		tube,
		L"compositePhongVS",
		L"coloredPhongSpherePS",
		playerColor
	);
	std::unique_ptr<Drawable> pBackRight = std::make_unique<SingleMeshDrawable>(
		renderer,
		dx::XMFLOAT3{ 0.2f, 0.0f, -0.3f },
		dx::XMFLOAT3{ dx::XM_PIDIV2, 0.0f, 0.0f },
		tube,
		L"compositePhongVS",
		L"coloredPhongSpherePS",
		playerColor
	);
	std::unique_ptr<Drawable> pMiddleTop = std::make_unique<SingleMeshDrawable>(
		renderer,
		dx::XMFLOAT3{ 0.0f, 1.0f, 0.57f },
		dx::XMFLOAT3{ dx::XM_PIDIV2, 0.0f, dx::XM_PIDIV2 },
		tube,
		L"compositePhongVS",
		L"coloredPhongSpherePS",
		playerColor
	);
	pFrontLeft->setScale(dx::XMFLOAT3{ 1.0f, 0.8f, 1.0f });
	pFrontRight->setScale(dx::XMFLOAT3{ 1.0f, 0.8f, 1.0f });
	this->addDrawable(std::move(pFrontLeft));
	this->addDrawable(std::move(pFrontRight));
	pBackLeft->setScale(dx::XMFLOAT3{ 1.0f, 0.9f, 1.0f });
	pBackRight->setScale(dx::XMFLOAT3{ 1.0f, 0.9f, 1.0f });
	this->addDrawable(std::move(pBackLeft));
	this->addDrawable(std::move(pBackRight));
	pMiddleTop->setScale(dx::XMFLOAT3{ 1.0f, 0.5f, 1.0f });
	this->addDrawable(std::move(pMiddleTop));


	// HANDLEBAR
	std::unique_ptr<Drawable> pLeftHandle = std::make_unique<SingleMeshDrawable>(
		renderer,
		dx::XMFLOAT3{ -0.35f, 0.99f, 0.5f },
		dx::XMFLOAT3{ dx::XM_PIDIV2 - 0.3f, 0.0f, -1.0f },
		tube,
		L"compositePhongVS",
		L"coloredPhongSpherePS",
		playerColor
	);
	std::unique_ptr<Drawable> pRightHandle = std::make_unique<SingleMeshDrawable>(
		renderer,
		dx::XMFLOAT3{ 0.35f, 0.99f, 0.5f },
		dx::XMFLOAT3{ dx::XM_PIDIV2 -0.3f, 0.0f, 1.0f }, //dx::XM_PI
		tube,
		L"compositePhongVS",
		L"coloredPhongSpherePS",
		playerColor
	);
	pLeftHandle->setScale(dx::XMFLOAT3{ 1.0f, 0.3f, 1.0f });
	pRightHandle->setScale(dx::XMFLOAT3{ 1.0f, 0.3f, 1.0f });
	this->addDrawable(std::move(pLeftHandle));
	this->addDrawable(std::move(pRightHandle));

	// LIGHTS
	Mesh lightM = Drawable::getMesh("sphere");
	std::unique_ptr<Drawable> plightD = std::make_unique<SingleMeshDrawable>(
		renderer,
		dx::XMFLOAT3{ 0.0f, 0.8f, 0.8f },
		dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f },
		lightM,
		L"compositePhongVS",
		L"coloredPhongSpherePS",
		playerColor
	);

	plightD->setScale(dx::XMFLOAT3{ 0.3f, 0.3f, 0.3f });
	this->addDrawable(std::move(plightD));
	this->pLight = std::make_shared<Light>(renderer, dx::XMFLOAT3{ 0.0f, 0.8f, 0.8f }, playerColor);

	float scale = 1.0f / 3.0f;
	this->setScale(dx::XMFLOAT3{ scale, scale, scale });
}

void MotocycleDrawable::update(float delta) noexcept {
	dx::XMFLOAT3 pos = this->position;
	pos.y = 0.5f;

	this->pLight->setPosition(pos);
	CompositeDrawable::update(delta);
}

std::shared_ptr<Light> MotocycleDrawable::getLight() const noexcept {
	return this->pLight;
}