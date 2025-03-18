#pragma once

#include "../core/event/keyboardEventManager.h"
#include "../core/event/mouseEventManager.h"
#include "../core/render/renderer.h"
#include "../core/window.h"
#include "../utils/image.h"
#include "../objects/drawable/drawable.h"

#include "../../utils/utils.h"

class Scene {
public:
	Scene(Renderer& renderer, std::string name);
	virtual ~Scene() = default;

	virtual void onLoad() = 0;

	virtual void update(float deltaTime);
	virtual void handleInput(Window& wnd, float delta) = 0;

	std::string getName() const noexcept;

protected:
	Renderer& renderer;
	std::string name;
	std::vector<std::unique_ptr<Drawable>> pDrawables;
};