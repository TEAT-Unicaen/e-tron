#include "renderer.h"
#include <memory>


Renderer::Renderer(HWND hwnd, int width, int height) {
	init(hwnd, width, height);
}

Renderer::~Renderer() {}

void Renderer::render() {
	swapChain->Present(1, 0);
}

void Renderer::fill(float r, float g, float b) {
	float clearColor[] = { r, g, b, 1.0f };
	deviceContext->ClearRenderTargetView(renderTargetView, clearColor);
}

void Renderer::init(HWND hwnd, int width, int height) {
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
	scd.BufferCount = 1;
	scd.BufferDesc.Width = width;
	scd.BufferDesc.Height = height;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hwnd;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.Windowed = TRUE;

	D3D_FEATURE_LEVEL featureLevels;
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, 
		D3D11_SDK_VERSION, &scd, &swapChain, 
		&device, &featureLevels, &deviceContext
	);
	if (FAILED(hr)) {
		throw WIN_EXCEPT(hr);
	}

	ID3D11Texture2D* backBuffer;
	swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
	device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);

}