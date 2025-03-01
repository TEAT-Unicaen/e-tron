#pragma once

#include <unordered_map>
#include <memory>
#include <thread>
#include <atomic>
#include <string>
#include <mutex>

#include "scene.h"

class SceneManager {
public:
	SceneManager() = delete;
	SceneManager(std::unique_ptr<Scene> loadingScene);
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	~SceneManager();

	void addScene(std::unique_ptr<Scene> scene);
	void changeScene(const std::string& sceneName);

	void update(float deltaTime);
	void handleInput(Window& wnd);

private:
	std::unordered_map<std::string, std::unique_ptr<Scene>> scenes;
	Scene* currentScene = nullptr;
	Scene* nextScene = nullptr;
	std::unique_ptr<Scene> loadingScene;
	std::thread loadingThread;
	// For thread safety
	std::atomic<bool> isLoading{ false };
	std::mutex loadingMutex;
};
