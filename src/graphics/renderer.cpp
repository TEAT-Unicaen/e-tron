#include "renderer.h"

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

	UINT swapChainCreateFlags = 0u;
#ifndef NDEBUG
	swapChainCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // !NDEBUG

	HR;
	CHECK_RENDERER_EXCEPT(D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, swapChainCreateFlags, nullptr, 0,
		D3D11_SDK_VERSION, &scd, &(this->pSwapChain),
		&(this->pDevice), nullptr, &(this->pDeviceContext)
	));

	Mwrl::ComPtr<ID3D11Resource> pBackBuffer;
	CHECK_RENDERER_EXCEPT(this->pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer));
	CHECK_RENDERER_EXCEPT(this->pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &(this->pRenderTargetView)));
}

void Renderer::render() {
	HR;
#ifndef NDEBUG
	this->infoManager.updateTheStartingPointIndex();
#endif // !NDEBUG

	if (FAILED(hr = this->pSwapChain->Present(1u, 0u))) {
		if (hr == DXGI_ERROR_DEVICE_REMOVED) {
			throw DEVICE_REMOVED_EXCEPT(this->pDevice->GetDeviceRemovedReason());
		} else {
			throw RENDERER_EXCEPT(hr);
		}
	}
}

void Renderer::fill(float r, float g, float b) {
	const float color[] = { r, g, b, 1.0f };
	this->pDeviceContext->ClearRenderTargetView(this->pRenderTargetView.Get(), color);
}