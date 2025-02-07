#include "renderer.h"
#include <memory>


Renderer::Renderer(HWND hwnd) {
	DXGI_SWAP_CHAIN_DESC scd = {};
	scd.BufferDesc.Width = 0;
	scd.BufferDesc.Height = 0;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 0;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 1;
	scd.OutputWindow = hwnd;
	scd.Windowed = TRUE;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = 0;


	D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0,
		D3D11_SDK_VERSION, &scd, &(this->pSwapChain),
		&(this->pDevice), nullptr, &(this->pDeviceContext)
	);

	ID3D11Resource* pBackBuffer = nullptr;
	this->pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer));
	if (pBackBuffer == nullptr) {
		throw std::runtime_error("Failed to get back buffer");
	}
	this->pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &(this->pRenderTargetView));
	pBackBuffer->Release();
}

Renderer::~Renderer() {
	if (this->pDeviceContext != nullptr) {
		this->pDeviceContext->Release();
	}
	if (this->pSwapChain != nullptr) {
		this->pSwapChain->Release();
	}
	if (this->pDevice != nullptr) {
		this->pDevice->Release();
	}
	if (this->pRenderTargetView != nullptr) {
		this->pRenderTargetView->Release();
	}
}

void Renderer::render() {
	this->pSwapChain->Present(1u, 0u);
}

void Renderer::fill(float r, float g, float b) {
	const float color[] = { r, g, b, 1.0f };
	this->pDeviceContext->ClearRenderTargetView(this->pRenderTargetView, color);
}