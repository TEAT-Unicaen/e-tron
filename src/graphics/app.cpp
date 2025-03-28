#include "app.h"


App::App()
	: wnd(800, 600, "E-Tron") {
	HR;
	// COM initialization
	CHECK_WIN32API_EXCEPT(CoInitialize(nullptr));

	this->wnd.keyEvent.disableAutorepeat();
	Renderer& renderer = this->wnd.getRenderer();
	ShaderManager& shaderManager = Drawable::shaderManager;

	// Add shaders
	shaderManager.addVertexShader(renderer, L"defaultVS");
	shaderManager.addVertexShader(renderer, L"texturedVS");
	shaderManager.addVertexShader(renderer, L"phongVS");
	shaderManager.addVertexShader(renderer, L"instanceVS");
	shaderManager.addVertexShader(renderer, L"instancePhongVS");
	shaderManager.addVertexShader(renderer, L"compositePhongVS");
	shaderManager.addVertexShader(renderer, L"gridPhongVS");

	shaderManager.addPixelShader(renderer, L"coloredCubePS");
	shaderManager.addPixelShader(renderer, L"coloredSquarePyramidPS");
	shaderManager.addPixelShader(renderer, L"coloredCylinderPS");
	shaderManager.addPixelShader(renderer, L"coloredCylinderTruncatedPS");
	shaderManager.addPixelShader(renderer, L"coloredSpherePS");
	shaderManager.addPixelShader(renderer, L"texturedPS");
	shaderManager.addPixelShader(renderer, L"coloredPhongCubePS");
	shaderManager.addPixelShader(renderer, L"coloredPhongSpherePS");
	shaderManager.addPixelShader(renderer, L"gridPhongPS");
	shaderManager.addPixelShader(renderer, L"instancePhongPS");

	// Add basic meshes
	Drawable::loadMesh("cube", Cube(renderer));
	Drawable::loadMesh("pyramid", Pyramid(renderer));
	Drawable::loadMesh("cylinder", Cylinder(renderer));
	Drawable::loadMesh("sphere", Sphere(renderer));
	Drawable::loadMesh("tore", Tore(renderer));
	Drawable::loadMesh("cone", Cone(renderer));
	Drawable::loadMesh("plane", Plane(renderer));

	// Add personnalisable meshes
	Drawable::loadMesh("Innerwheel", Cylinder(renderer, 0.3f, 0.35f));
	Drawable::loadMesh("Outerwheel", Tore(renderer, 0.35f, 0.15f));
	Drawable::loadMesh("tube", Cylinder(renderer, 0.05f, 1.0f));
	Drawable::loadMesh("Innerbase", Cylinder(renderer, 0.2f ,0.30f, 4));
	Drawable::loadMesh("Outerbase", Cylinder(renderer, 0.3f, 0.35f, 4));

	std::shared_ptr<Image> splashScreen = std::make_shared<Image>(L"assets/img/intro.gif");


	UINT volumeLevel = 0xFFFF / 3;
	waveOutSetVolume(NULL, MAKELONG(volumeLevel, volumeLevel));
	std::atomic<bool> splashScreenDone = false;
	auto splashThread = std::thread([splashScreen, &renderer, &splashScreenDone]() {
		for (int i = 0; i < 110; i++) {
			renderer.renderImage(splashScreen, dx::XMFLOAT2(0, 0), dx::XMFLOAT2(800, 600));
			renderer.render();
			if (i == 50) {
				OutputDebugStringA("SOUND\n");
				PlaySoundA((LPCSTR)"./assets/sound/intro.wav", NULL, SND_FILENAME | SND_ASYNC);
			}
			if (i < 89) {
				splashScreen->nextFrame();
			}
			SLEEP_MS(20);
		}
		splashScreenDone = true;  // Marquer que l'écran de splash est terminé
		});

	// Attendre que le thread de splash se termine
	while (!splashScreenDone.load(std::memory_order_acquire)) {
		wnd.processMessages();
	}

	// Joindre le thread avant de quitter
	splashThread.join();

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
		float delta = this->timer.mark();
		this->checkInput(delta);
		this->update(delta);
		//SLEEP_MS(1);
	}
}

void App::checkInput(float delta) {
	if (this->wnd.keyEvent.keyIsPressed(VK_DELETE)) {
		this->diplaysFPS = !this->diplaysFPS;
	}
	this->sceneManager->handleInput(this->wnd, delta);
}

void App::update(float delta) {
	Renderer& renderer = this->wnd.getRenderer();
	
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
	if (this->diplaysFPS) {
		renderer.renderText(L"FPS : " + std::to_wstring(this->fps), dx::XMFLOAT2(10, 10), 16, Color::WHITE);
	}
	renderer.render();
}