#include "scene.h"

Scene::Scene(Renderer& renderer, std::string name) : renderer(renderer), name(name) {}

void Scene::update(float deltaTime) {
	for (auto& pDrawable : this->pDrawables) {
		pDrawable->update(deltaTime);
		pDrawable->draw(this->renderer);
	}
}

std::string Scene::getName() const noexcept {
	return this->name;
}