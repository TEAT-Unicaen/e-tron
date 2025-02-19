#include "texture.h"

Texture::Texture(Renderer& renderer, const Image& image) {
	HR_PLUS;
	// Create the texture
	D3D11_TEXTURE2D_DESC textureDesc = {};
	textureDesc.Width = image.getWidth();
	textureDesc.Height = image.getHeight();
	textureDesc.MipLevels = 1u;
	textureDesc.ArraySize = 1u;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1u;
	textureDesc.SampleDesc.Quality = 0u;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0u;
	textureDesc.MiscFlags = 0u;
	D3D11_SUBRESOURCE_DATA textureData = {};
	textureData.pSysMem = image.getData();
	textureData.SysMemPitch = image.getWidth() * 4;
	Mwrl::ComPtr<ID3D11Texture2D> pTexture;
	CHECK_RENDERER_EXCEPT_NO_INFO(this->getDevice(renderer)->CreateTexture2D(
		&textureDesc,
		&textureData,
		&pTexture
	));
	// Create the texture view
	D3D11_SHADER_RESOURCE_VIEW_DESC textureViewDesc = {};
	textureViewDesc.Format = textureDesc.Format;
	textureViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	textureViewDesc.Texture2D.MostDetailedMip = 0u;
	textureViewDesc.Texture2D.MipLevels = 1u;
	CHECK_RENDERER_EXCEPT(this->getDevice(renderer)->CreateShaderResourceView(
		pTexture.Get(),
		&textureViewDesc,
		&this->pTextureView
	));
}

void Texture::bind(Renderer& renderer) {
	HR_PLUS;
	CHECK_INFO_ONLY_EXCEPT(this->getDeviceContext(renderer)->PSSetShaderResources(0u, 1u, this->pTextureView.GetAddressOf()));
}