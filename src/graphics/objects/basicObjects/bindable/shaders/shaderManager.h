#pragma once

#include "vertexShader.h"
#include "pixelShader.h"
#include "hullShader.h"
#include "domainShader.h"
#include "geometryShader.h"
#include "computeShader.h"

#include <unordered_map>
#include <memory>

class ShaderManager {
public:
	ShaderManager();

	void addVertexShader(Renderer& renderer, const std::wstring& filename);
	void addPixelShader(Renderer& renderer, const std::wstring& filename);
	void addHullShader(Renderer& renderer, const std::wstring& filename);
	void addDomainShader(Renderer& renderer, const std::wstring& filename);
	void addGeometryShader(Renderer& renderer, const std::wstring& filename);
	void addComputeShader(Renderer& renderer, const std::wstring& filename);
	
	std::shared_ptr<VertexShader> getVertexShader(const std::wstring& filename);
	std::shared_ptr<PixelShader> getPixelShader(const std::wstring& filename);
	std::shared_ptr<HullShader> getHullShader(const std::wstring& filename);
	std::shared_ptr<DomainShader> getDomainShader(const std::wstring& filename);
	std::shared_ptr<GeometryShader> getGeometryShader(const std::wstring& filename);
	std::shared_ptr<ComputeShader> getComputeShader(const std::wstring& filename);
	
private:
	std::unordered_map<std::wstring, std::shared_ptr<VertexShader>> vertexShaders;
	std::unordered_map<std::wstring, std::shared_ptr<PixelShader>> pixelShaders;
	std::unordered_map<std::wstring, std::shared_ptr<HullShader>> hullShaders;
	std::unordered_map<std::wstring, std::shared_ptr<DomainShader>> domainShaders;
	std::unordered_map<std::wstring, std::shared_ptr<GeometryShader>> geometryShaders;
	std::unordered_map<std::wstring, std::shared_ptr<ComputeShader>> computeShaders;
};