#include "renderer.h"

Renderer::Renderer(HWND hwnd, int width, int height) 
	: camera(Camera()) {
	DXGI_SWAP_CHAIN_DESC scd = {};
	scd.BufferDesc.Width = width;
	scd.BufferDesc.Height = height;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 32-bit RGBA color
	scd.BufferDesc.RefreshRate.Numerator = 0;//FPS MAX
	scd.BufferDesc.RefreshRate.Denominator = 0;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; // No scaling
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; // No scanline ordering
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 2;
	scd.OutputWindow = hwnd;
	scd.Windowed = TRUE;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // Discard the previous buffer
	scd.Flags = 0u;

	UINT swapChainCreateFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT; // for the 2D renderer
#ifndef NDEBUG
	swapChainCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // !NDEBUG

	HR;

	// Create the device, the device context and the swap chain
	CHECK_RENDERER_EXCEPT(D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, swapChainCreateFlags, nullptr, 0,
		D3D11_SDK_VERSION, &scd, &(this->pSwapChain),
		&(this->pDevice), nullptr, &(this->pDeviceContext)
	));

	// Create the Render Target View, store subresource can be accessed during the rendering
	Mwrl::ComPtr<ID3D11Resource> pBackBuffer;
	CHECK_RENDERER_EXCEPT(this->pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer)));
	CHECK_RENDERER_EXCEPT(this->pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &this->pRenderTargetView));

	
	// Z-Buffer creation //

	// Create the depth stencil state (Controls how depth comparisons are performed)
	D3D11_DEPTH_STENCIL_DESC dsd = {};
	dsd.DepthEnable = TRUE;
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsd.DepthFunc = D3D11_COMPARISON_LESS;
	Mwrl::ComPtr<ID3D11DepthStencilState> pDSState;
	CHECK_RENDERER_EXCEPT(this->pDevice->CreateDepthStencilState(&dsd, &pDSState));
	this->pDeviceContext->OMSetDepthStencilState(pDSState.Get(), 1u);


	// Create the depth stencil texture (Stores depth values for per-pixel comparisons)
	Mwrl::ComPtr<ID3D11Texture2D> pDepthStencil;
	D3D11_TEXTURE2D_DESC td = {};
	td.Width = width;
	td.Height = height;
	td.MipLevels = 1u;
	td.ArraySize = 1u;
	td.Format = DXGI_FORMAT_D32_FLOAT;
	td.SampleDesc.Count = 1u;
	td.SampleDesc.Quality = 0u;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	CHECK_RENDERER_EXCEPT(this->pDevice->CreateTexture2D(&td, nullptr, &pDepthStencil));

	// Create the depth stencil view (Provides access to the texture for use as a depth buffer)
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd = {};
	dsvd.Format = DXGI_FORMAT_D32_FLOAT;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Texture2D.MipSlice = 0u;
	CHECK_RENDERER_EXCEPT(this->pDevice->CreateDepthStencilView(pDepthStencil.Get(), &dsvd, &this->pDepthStencilView));

	this->pDeviceContext->OMSetRenderTargets(1u, this->pRenderTargetView.GetAddressOf(), this->pDepthStencilView.Get());

	D3D11_VIEWPORT viewport = {};
	viewport.Width = (float)width;
	viewport.Height = (float)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	this->pDeviceContext->RSSetViewports(1u, &viewport);

	// Set up the 2D
	D2D1_FACTORY_OPTIONS options = {};
#ifndef NDEBUG
	options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif // !NDEBUG

	CHECK_RENDERER_EXCEPT(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory),&options, &this->pD2DFactory));
	CHECK_RENDERER_EXCEPT(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), &this->pDWriteFactory)); // the MACRO don't work here

	Mwrl::ComPtr<IDXGISurface> pBackBufferDxgi;
	CHECK_RENDERER_EXCEPT(this->pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBufferDxgi)));

	D2D1_RENDER_TARGET_PROPERTIES rtProps = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_HARDWARE,
		D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_IGNORE), // Match swap chain format
		0.0f,
		0.0f,
		D2D1_RENDER_TARGET_USAGE_NONE,
		D2D1_FEATURE_LEVEL_DEFAULT
	);

    CHECK_RENDERER_EXCEPT(this->pD2DFactory->CreateDxgiSurfaceRenderTarget(pBackBufferDxgi.Get(), &rtProps, &this->pD2DRenderTarget));

	CHECK_RENDERER_EXCEPT(this->pDWriteFactory->CreateTextFormat(
		L"Segoe UI",                // Font family
		nullptr,                    // Font collection
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		24.0f,                      // Font size
		L"",                   // Locale
		&this->pTextFormat
	));

	CHECK_RENDERER_EXCEPT(this->pD2DRenderTarget->CreateSolidColorBrush(Color::BLACK.toD2D1ColorF(), &this->pBrush));


	// Camera initialization
	this->camera.setPosition(0.0f, 0.0f, -5.0f);
	this->camera.setAspectRatio(static_cast<float>(width) / static_cast<float>(height));
}

void Renderer::render() {
	HR;
#ifndef NDEBUG
	this->infoManager.updateTheStartingPointIndex();
#endif // !NDEBUG

	if (FAILED(hr = this->pSwapChain->Present(this->syncInterval, 0u))) {
		if (hr == DXGI_ERROR_DEVICE_REMOVED) {
			throw DEVICE_REMOVED_EXCEPT(this->pDevice->GetDeviceRemovedReason());
		} else {
			throw RENDERER_EXCEPT(hr);
		}
	}
}

void Renderer::fill(Color color) {
	const float c[4] = { color.r, color.g, color.b, color.a };
	this->pDeviceContext->ClearRenderTargetView(this->pRenderTargetView.Get(), c);
	this->pDeviceContext->ClearDepthStencilView(this->pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void Renderer::drawIndexed(UINT count) noexcept(!IS_DEBUG_MODE) {
	this->pDeviceContext->DrawIndexed(count, 0u, 0u);
}

void Renderer::drawIndexedInstanced(UINT IndexCountPerInstance, UINT InstanceCount) noexcept(!IS_DEBUG_MODE) {
	this->pDeviceContext->DrawIndexedInstanced(IndexCountPerInstance, InstanceCount, 0u, 0, 0u);
}

dx::XMMATRIX Renderer::getProjection() const noexcept {
	return this->camera.getProjection();
}

Camera& Renderer::getCamera() noexcept {
	return camera;
}

dx::XMMATRIX Renderer::getView() const noexcept {
	return this->camera.getView();
}

void Renderer::renderText(const std::wstring& text, const dx::XMFLOAT2& position, float size, Color color) {
	HR;
	// Set the brush color
	pBrush->SetColor(color.toD2D1ColorF());
	// Begin drawing to the Direct2D render target
	pD2DRenderTarget->BeginDraw();

	// Create a DirectWrite text layout
	Mwrl::ComPtr<IDWriteTextLayout> pTextLayout;
	CHECK_RENDERER_EXCEPT(this->pDWriteFactory->CreateTextLayout(
		text.c_str(),
		static_cast<UINT32>(text.length()),
		pTextFormat.Get(),
		FLT_MAX,  // Max width (use entire width)
		FLT_MAX,  // Max height (use entire height)
		&pTextLayout
	));

	// Draw the text on the screen
	pD2DRenderTarget->DrawTextLayout(D2D1::Point2F(position.x, position.y), pTextLayout.Get(), pBrush.Get());

	// End drawing
	pD2DRenderTarget->EndDraw();
}

void Renderer::setVSync(bool vsync) {
	this->syncInterval = vsync ? 1u : 0u;
}

void Renderer::resize(int newWidth, int newHeight) {
	if (newWidth == 0 || newHeight == 0) return; // Éviter un resize inutile

	// Relâcher les ressources dépendantes du swap chain
	this->pRenderTargetView.Reset();
	this->pDepthStencilView.Reset();
	this->pD2DRenderTarget.Reset();
	HR;
	// Redimensionner le swap chain
	RENDERER_EXCEPT(this->pSwapChain->ResizeBuffers(0, newWidth, newHeight, DXGI_FORMAT_UNKNOWN, 0));

	// Recréer le Render Target View
	Mwrl::ComPtr<ID3D11Texture2D> pBackBuffer;
	CHECK_RENDERER_EXCEPT(this->pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer)));
	CHECK_RENDERER_EXCEPT(this->pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &this->pRenderTargetView));

	// Recréer le Depth Stencil Buffer
	D3D11_TEXTURE2D_DESC td = {};
	td.Width = newWidth;
	td.Height = newHeight;
	td.MipLevels = 1u;
	td.ArraySize = 1u;
	td.Format = DXGI_FORMAT_D32_FLOAT;
	td.SampleDesc.Count = 1u;
	td.SampleDesc.Quality = 0u;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	Mwrl::ComPtr<ID3D11Texture2D> pDepthStencil;
	CHECK_RENDERER_EXCEPT(this->pDevice->CreateTexture2D(&td, nullptr, &pDepthStencil));

	// Recréer la Depth Stencil View
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd = {};
	dsvd.Format = DXGI_FORMAT_D32_FLOAT;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Texture2D.MipSlice = 0u;
	CHECK_RENDERER_EXCEPT(this->pDevice->CreateDepthStencilView(pDepthStencil.Get(), &dsvd, &this->pDepthStencilView));

	this->pDeviceContext->OMSetRenderTargets(1u, this->pRenderTargetView.GetAddressOf(), this->pDepthStencilView.Get());

	// Mettre à jour le viewport
	D3D11_VIEWPORT viewport = {};
	viewport.Width = static_cast<float>(newWidth);
	viewport.Height = static_cast<float>(newHeight);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	this->pDeviceContext->RSSetViewports(1u, &viewport);

	// Recréer le render target pour Direct2D
	Mwrl::ComPtr<IDXGISurface> pBackBufferDxgi;
	CHECK_RENDERER_EXCEPT(this->pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBufferDxgi)));

	D2D1_RENDER_TARGET_PROPERTIES rtProps = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_HARDWARE,
		D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
		0.0f, 0.0f,
		D2D1_RENDER_TARGET_USAGE_NONE,
		D2D1_FEATURE_LEVEL_DEFAULT
	);

	CHECK_RENDERER_EXCEPT(this->pD2DFactory->CreateDxgiSurfaceRenderTarget(pBackBufferDxgi.Get(), &rtProps, &this->pD2DRenderTarget));

	// Mettre à jour l'aspect ratio de la caméra
	this->camera.setAspectRatio(static_cast<float>(newWidth) / static_cast<float>(newHeight));
}

void Renderer::renderImage(const std::shared_ptr<Image>& image, const dx::XMFLOAT2& position, const dx::XMFLOAT2& size) {
	HR;

	// Create a Direct2D bitmap properties structure
	D2D1_BITMAP_PROPERTIES bitmapProperties = {
		{ DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED  }, // BGRA format
		96.0f, 96.0f  // DPI
	};


	UINT32 width = image->getWidth();
	// Create the Direct2D bitmap from the BYTE[] data
	Mwrl::ComPtr<ID2D1Bitmap> pBitmap;
	CHECK_RENDERER_EXCEPT(pD2DRenderTarget->CreateBitmap(
		D2D1::SizeU(width, image->getHeight()),  // Size of the bitmap
		image->getData(),                       // The pixel data (BYTE array)
		width * 4,                   // Stride (4 bytes per pixel for BGRA)
		&bitmapProperties,           // Bitmap properties (format, DPI, etc.)
		&pBitmap
	));

	// Begin drawing to the Direct2D render target
	pD2DRenderTarget->BeginDraw();

	// Calculate destination rectangle
	D2D1_RECT_F destRect = D2D1::RectF(
		position.x, position.y,
		position.x + size.x, position.y + size.y
	);

	// Draw the bitmap on the screen
	pD2DRenderTarget->DrawBitmap(pBitmap.Get(), destRect);

	// End drawing
	pD2DRenderTarget->EndDraw();
}