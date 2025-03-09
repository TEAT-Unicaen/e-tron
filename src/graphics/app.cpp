#include "app.h"


App::App()
	: wnd(800, 600, "E-Tron") {
	HR;
	// COM initialization
	CHECK_WIN32API_EXCEPT(CoInitialize(nullptr));

	Renderer& renderer = this->wnd.getRenderer();
	ShaderManager& shaderManager = Drawable::shaderManager;

	// Add shaders
	shaderManager.addVertexShader(renderer, L"defaultVS");
	shaderManager.addVertexShader(renderer, L"textureVS");

	shaderManager.addPixelShader(renderer, L"coloredCubePS");
	shaderManager.addPixelShader(renderer, L"coloredSquarePyramidPS");
	shaderManager.addPixelShader(renderer, L"coloredCylinderPS");
	shaderManager.addPixelShader(renderer, L"coloredCylinderTruncatedPS");
	shaderManager.addPixelShader(renderer, L"coloredSpherePS");
	shaderManager.addPixelShader(renderer, L"coloredMotorcyclePS");
	shaderManager.addPixelShader(renderer, L"texturePS");

	shaderManager.addVertexShader(renderer, L"phongVS");
	shaderManager.addPixelShader(renderer, L"phongPS");


	this->sceneManager = std::make_unique<SceneManager>(
		std::make_unique<LoadingScene>(
			renderer,
			"loadingScene"
		)
	);

	// Add scenes
	this->sceneManager->addScene(std::make_unique<GameScene>(renderer, "gameScene"));
	this->sceneManager->changeScene("gameScene");

}

App::~App() {
	CoUninitialize();
}

int App::run() {
	while (true) { // !!! gResult > 0 but not GetMessage > 0
		//Check the window messages and quit 
		if (const auto eCode = wnd.processMessages()) {
			return *eCode;
		}
		this->checkInput();
		this->update();
		//SLEEP_MS(1);
	}
}

void App::checkInput() {
	this->sceneManager->handleInput(this->wnd);
}

void App::update() {
	Renderer& renderer = this->wnd.getRenderer();
	float delta = this->timer.mark();
	this->frameTime += delta;  // Accumulate frame time
	this->frameCount++;  // Increment the frame count

	// Calculate FPS every second
	if (this->frameTime >= 1.0f) {
		this->fps = this->frameCount;  // Set FPS to the number of frames in the last second
		this->frameTime = 0.0f;  // Reset frame time
		this->frameCount = 0;    // Reset frame count
	}

	// Update the scene
	renderer.fill(Color::BLACK);
	this->sceneManager->update(delta);

	renderer.renderText(L"FPS : " + std::to_wstring(this->fps), dx::XMFLOAT2(10, 10), 16, Color::WHITE);
	renderer.render();
}