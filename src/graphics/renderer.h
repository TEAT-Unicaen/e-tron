#pragma once 
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <Windows.h> // Assure que HWND est reconnu
#include <wrl.h>
#include <stdexcept>

namespace Mwrl = Microsoft::WRL;

struct Vertex {
	float x, y, z;  // Position dans l'espace 3D
	float r, g, b, a;  // Couleur RGBA
};

class Renderer {

public:
	Renderer(HWND hwnd);
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	~Renderer() = default;

	void render();
	void fill(float r, float g, float b);

private:
	// Direct3D globals
	Mwrl::ComPtr<ID3D11Device> pDevice;
	Mwrl::ComPtr<ID3D11DeviceContext> pDeviceContext;
	Mwrl::ComPtr<IDXGISwapChain> pSwapChain;
	Mwrl::ComPtr<ID3D11RenderTargetView> pRenderTargetView;


	ID3D11Buffer* vertexBuffer;  // Buffer pour les vertices de la grille
	UINT vertexCount;  // Nombre de vertices

};