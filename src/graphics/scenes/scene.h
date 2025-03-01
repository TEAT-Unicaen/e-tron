#pragma once

#include "../event/keyboardEventManager.h"
#include "../event/mouseEventManager.h"
#include "../core/renderer.h"
#include "../core/window.h"
#include "../utils/image.h"
#include "../objects/object.h"

#include "../../utils/utils.h"

class Scene {
public:
	Scene(Renderer& renderer, std::string name);
	virtual ~Scene() = default;

	virtual void onLoad() = 0;

	virtual void update(float deltaTime);
	virtual void handleInput(Window& wnd) = 0;

	std::string getName() const noexcept;

protected:
	Renderer& renderer;
	std::string name;
	std::vector<std::unique_ptr<Object>> pDrawables;
};