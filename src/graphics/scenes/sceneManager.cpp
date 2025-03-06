#include "sceneManager.h"

SceneManager::SceneManager(std::unique_ptr<Scene> loadingScene)
	: loadingScene(std::move(loadingScene)) {
	this->loadingScene->onLoad();
	//this->currentScene = this->loadingScene.get();
}

SceneManager::~SceneManager() {
	if (this->loadingThread.joinable()) {
		this->loadingThread.join();
	}
}

void SceneManager::addScene(std::unique_ptr<Scene> scene) {
	// Add the scene to the scenes map with its name
	this->scenes[scene->getName()] = std::move(scene);
}

void SceneManager::changeScene(const std::string& sceneName) {
	// Check if the requested scene exists
	if (this->scenes.find(sceneName) == this->scenes.end()) {
		return; // Scene not found
	}

	if (this->isLoading) {
		return;
	}

	// Start by displaying the loading scene
	if (this->loadingScene) {
		this->currentScene = this->loadingScene.get();
	}

	// Set the loading flag to true
	{
		std::lock_guard<std::mutex> lock(this->loadingMutex);
		this->isLoading = true;
	}

	if (this->loadingThread.joinable()) {
		this->loadingThread.join();
	}

	OutputDebugStringA(("Loading scene: " + sceneName + "\n").c_str());
	// Create a new thread to load the next scene in the background
	this->loadingThread = std::thread([this, sceneName]() {
		this->nextScene = this->scenes[sceneName].get();
		HR;
		CHECK_WIN32API_EXCEPT(CoInitialize(nullptr));
		this->nextScene->onLoad();
		CoUninitialize();

		// Once the scene is loaded, update the flag and switch to the new scene
		{
			std::lock_guard<std::mutex> lock(this->loadingMutex);
			this->isLoading = false;
		}
		});

	this->loadingThread.detach(); // Detach the thread to run independently
}

void SceneManager::update(float deltaTime) {
	if (!this->isLoading && this->nextScene) {
		// Switch to the newly loaded scene
		this->currentScene = this->nextScene;
		this->nextScene = nullptr;
	}

	if (this->currentScene) {
		this->currentScene->update(deltaTime);
	}
}

void SceneManager::handleInput(Window& wnd) {
	if (this->currentScene) {
		this->currentScene->handleInput(wnd);
	}
}
