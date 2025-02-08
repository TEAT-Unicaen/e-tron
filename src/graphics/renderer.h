#pragma once 
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <wrl.h>
#include <d3dcompiler.h>
#pragma comment(lib, "D3dcompiler.lib")

#include "setUpWindows.h" // Assure que HWND est reconnu
#include "exception/rendererException.h"

namespace Mwrl = Microsoft::WRL;

class Renderer {
public:
	typedef struct Vertex {
		struct {
			float x;
			float y;
		} pos;
		struct {
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
		} color;
	} Vertex;
	Renderer(HWND hwnd, int width, int height);
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	~Renderer() = default;

	void render();
	void fill(UINT r, UINT g, UINT b);

	void addPoint(Vertex v);
	void addLine(Vertex v1, Vertex v2);
	void addTriangle(Vertex v1, Vertex v2, Vertex v3);

	void drawAllPoint();
	void drawAllLine();
	void drawAllTriangle();
	void drawAll();
private:
	void drawVertex(std::vector<Vertex>& vertices, D3D11_PRIMITIVE_TOPOLOGY topology);
#ifndef NDEBUG
	DxgiInfoManager infoManager;
#endif // !NDEBUG

	// Direct3D globals
	Mwrl::ComPtr<ID3D11Device> pDevice;
	Mwrl::ComPtr<ID3D11DeviceContext> pDeviceContext;
	Mwrl::ComPtr<IDXGISwapChain> pSwapChain;
	Mwrl::ComPtr<ID3D11RenderTargetView> pRenderTargetView;

	//all Vertices
	std::vector<Vertex> points;
	std::vector<Vertex> lines;
	std::vector<Vertex> triangles;

	// Renderer exception macros
#ifndef NDEBUG // in Debug mode
	#define RENDERER_EXCEPT(hr) RendererHrException(__LINE__, __FILE__, hr, this->infoManager.getMessages())
	#define RENDERER_LAST_EXCEPT() RENDERER_EXCEPT(GetLastError())
	#define DEVICE_REMOVED_EXCEPT(hr) DeviceRemovedException(__LINE__, __FILE__, hr, this->infoManager.getMessages())

	#define CHECK_RENDERER_EXCEPT(hrcall) this->infoManager.updateTheStartingPointIndex(); if (FAILED(hr = (hrcall))) throw RENDERER_EXCEPT(hr)
	#define CHECK_INFO_ONLY_EXCEPT(call) this->infoManager.updateTheStartingPointIndex(); (call); {auto v = this->infoManager.getMessages(); if(!v.empty()) {throw INFO_ONLY_EXCEPT(v);}}
#else // in Release mode
	#define RENDERER_EXCEPT(hr) RendererHrException(__LINE__, __FILE__, hr)
	#define RENDERER_LAST_EXCEPT() RENDERER_EXCEPT(GetLastError())
	#define DEVICE_REMOVED_EXCEPT(hr)  DeviceRemovedException(__LINE__, __FILE__, hr)

	#define CHECK_RENDERER_EXCEPT(hrcall) if (FAILED(hr = (hrcall))) throw RENDERER_EXCEPT(hr)
	#define CHECK_INFO_ONLY_EXCEPT(call) call
#endif // !NDEBUG
};
// Color macro
#define WHITE 255, 255, 255
#define BLACK 0, 0, 0
#define RED 255, 0, 0
#define GREEN 0, 255, 0
#define BLUE 0, 0, 255
