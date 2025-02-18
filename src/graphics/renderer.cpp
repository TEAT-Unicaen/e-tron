#include "renderer.h"

Renderer::Renderer(HWND hwnd, int width, int height) {
	DXGI_SWAP_CHAIN_DESC scd = {};
	scd.BufferDesc.Width = width;
	scd.BufferDesc.Height = height;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 32-bit RGBA color
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 0;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; // No scaling
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; // No scanline ordering
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 1;
	scd.OutputWindow = hwnd;
	scd.Windowed = TRUE;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // Discard the previous buffer
	scd.Flags = 0;

	UINT swapChainCreateFlags = 0u;
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
	CHECK_RENDERER_EXCEPT(this->pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer));
	CHECK_RENDERER_EXCEPT(this->pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &(this->pRenderTargetView)));

	
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

void Renderer::fill(UINT r, UINT g, UINT b) {
	const float color[] = { (float)r, (float)g, (float)b, 1.0f };
	this->pDeviceContext->ClearRenderTargetView(this->pRenderTargetView.Get(), color);
	this->pDeviceContext->ClearDepthStencilView(this->pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void Renderer::addPoint(Vertex v) {
	this->points.push_back(v);
}

void Renderer::addLine(Vertex v1, Vertex v2) {
	this->lines.push_back(v1);
	this->lines.push_back(v2);
}


void Renderer::addTriangle(Vertex v1, Vertex v2, Vertex v3) {
	this->triangles.push_back(v1);
	this->triangles.push_back(v2);
	this->triangles.push_back(v3);
}

void Renderer::drawVertex(std::vector<Vertex>& vertices, D3D11_PRIMITIVE_TOPOLOGY topology) {
	// if there is no vertex, return
	if (vertices.size() == 0) {
		return;
	}
	OutputDebugStringA("Drawing vertices\n");
	// Create the vertex buffer
	Mwrl::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = sizeof(Vertex) * (UINT)vertices.size();
	bd.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertices.data();
	CHECK_INFO_ONLY_EXCEPT(this->pDevice->CreateBuffer(&bd, &sd, &pVertexBuffer));

	// Set the previous buffer in the pipeline
	UINT stride = sizeof(Vertex);
	UINT offset = 0u;
	this->pDeviceContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
	
	// set the pixel shader in the pipeline
	Mwrl::ComPtr<ID3D11PixelShader> pPixelShader;
	Mwrl::ComPtr<ID3DBlob> pBlob;
	CHECK_INFO_ONLY_EXCEPT(D3DReadFileToBlob(L"shaders/pixelShader.cso", &pBlob));
	CHECK_INFO_ONLY_EXCEPT(this->pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader));
	this->pDeviceContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);

	// set the vertex shader in the pipeline
	Mwrl::ComPtr<ID3D11VertexShader> pVertexShader;
	CHECK_INFO_ONLY_EXCEPT(D3DReadFileToBlob(L"shaders/vertexShader.cso", &pBlob));
	CHECK_INFO_ONLY_EXCEPT(this->pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader));
	this->pDeviceContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);

	// set the input layout in the pipeline
	Mwrl::ComPtr<ID3D11InputLayout> pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[] = {
		{"Position", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0u},
		{"Color", 0u, DXGI_FORMAT_R8G8B8A8_UNORM, 0u, 12u, D3D11_INPUT_PER_VERTEX_DATA, 0u}
	};
	CHECK_INFO_ONLY_EXCEPT(this->pDevice->CreateInputLayout(
		ied, (UINT)std::size(ied), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout)
	);
	this->pDeviceContext->IASetInputLayout(pInputLayout.Get());

	// Set the primitive topology in the pipeline aka the drawing mode
	this->pDeviceContext->IASetPrimitiveTopology(topology);

	// Draw the vertices
	CHECK_INFO_ONLY_EXCEPT(this->pDeviceContext->Draw((UINT)vertices.size(), 0u));
}

void Renderer::drawAllPoint() {
	this->drawVertex(this->points, D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
}

void Renderer::drawAllLine() {
	this->drawVertex(this->lines, D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
}

void Renderer::drawAllTriangle() {
	this->drawVertex(this->triangles, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Renderer::drawAll() {
	this->drawAllPoint();
	this->drawAllLine();
	this->drawAllTriangle();
}