#pragma once

#include "../event/keyboardEventManager.h"
#include "../event/mouseEventManager.h"
#include "../core/renderer.h"

#include "sceneManager.h"

class Scene {
public:
	virtual ~Scene() = default;

	virtual void onLoad() = 0; // Load the scene

	virtual void update(float deltaTime) = 0;  // Update logic for the scene
	virtual void render(Renderer& renderer) = 0; // Render the scene
	virtual void handleInput(const KeyboardEventManager& keyevent, const MouseEventManager&) = 0; // Handle input for the scene

	virtual std::string getName() const = 0; // Get the name of the scene
};
