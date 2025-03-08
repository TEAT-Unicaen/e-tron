#include "shaderManager.h"

ShaderManager::ShaderManager() {
	UINT size = 5;
	this->vertexShaders.reserve(size);
	this->pixelShaders.reserve(size);
	this->hullShaders.reserve(size);
	this->domainShaders.reserve(size);
	this->geometryShaders.reserve(size);
	this->computeShaders.reserve(size);
}

void ShaderManager::addVertexShader(Renderer& renderer, const std::wstring& filename) {
	vertexShaders[filename] = std::make_shared<VertexShader>(renderer, filename);
}

void ShaderManager::addPixelShader(Renderer& renderer, const std::wstring& filename) {
	pixelShaders[filename] = std::make_shared<PixelShader>(renderer, filename);
}

void ShaderManager::addHullShader(Renderer& renderer, const std::wstring& filename) {
	hullShaders[filename] = std::make_shared<HullShader>(renderer, filename);
}

void ShaderManager::addDomainShader(Renderer& renderer, const std::wstring& filename) {
	domainShaders[filename] = std::make_shared<DomainShader>(renderer, filename);
}

void ShaderManager::addGeometryShader(Renderer& renderer, const std::wstring& filename) {
	geometryShaders[filename] = std::make_shared<GeometryShader>(renderer, filename);
}

void ShaderManager::addComputeShader(Renderer& renderer, const std::wstring& filename) {
	computeShaders[filename] = std::make_shared<ComputeShader>(renderer, filename);
}

std::shared_ptr<VertexShader> ShaderManager::getVertexShader(const std::wstring& filename) {
	return vertexShaders[filename];
}

std::shared_ptr<PixelShader> ShaderManager::getPixelShader(const std::wstring& filename) {
	return pixelShaders[filename];
}

std::shared_ptr<HullShader> ShaderManager::getHullShader(const std::wstring& filename) {
	return hullShaders[filename];
}

std::shared_ptr<DomainShader> ShaderManager::getDomainShader(const std::wstring& filename) {
	return domainShaders[filename];
}

std::shared_ptr<GeometryShader> ShaderManager::getGeometryShader(const std::wstring& filename) {
	return geometryShaders[filename];
}

std::shared_ptr<ComputeShader> ShaderManager::getComputeShader(const std::wstring& filename) {
	return computeShaders[filename];
}
