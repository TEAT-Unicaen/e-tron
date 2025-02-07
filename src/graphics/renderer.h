#pragma once 
#include <d3d11.h>
#include <Windows.h> // Assure que HWND est reconnu
#pragma comment(lib, "d3d11.lib")

#include "window.h"

struct Vertex {
	float x, y, z;  // Position dans l'espace 3D
	float r, g, b, a;  // Couleur RGBA
};


class Renderer {

public:
	Renderer(HWND hwnd);
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	~Renderer();

	void render();
	void fill(float r, float g, float b);

private:
	// Direct3D globals
	ID3D11Device* pDevice = nullptr;
	ID3D11DeviceContext* pDeviceContext = nullptr;
	IDXGISwapChain* pSwapChain = nullptr;
	ID3D11RenderTargetView* pRenderTargetView = nullptr;


	ID3D11Buffer* vertexBuffer;  // Buffer pour les vertices de la grille
	UINT vertexCount;  // Nombre de vertices

};