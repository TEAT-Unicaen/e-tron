#include "image.h"

Image::Image(const std::wstring& path) {
	HR;
	// Create the WIC factory
	CHECK_WIN32API_EXCEPT(CoCreateInstance(
		CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&this->wicFactory)
	));

	// Load the image
	Mwrl::ComPtr<IWICBitmapDecoder> wicDecoder;
	CHECK_WIN32API_EXCEPT(this->wicFactory->CreateDecoderFromFilename(
		path.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &wicDecoder
	));

	// Get the number of frames
	CHECK_WIN32API_EXCEPT(wicDecoder->GetFrameCount(&this->frameCount));
	this->currentFrameIndex = 0; // Start at the first frame

	// Load all frames
	this->frames.resize(this->frameCount);
	for (UINT i = 0; i < this->frameCount; i++) {
		CHECK_WIN32API_EXCEPT(wicDecoder->GetFrame(i, &this->frames[i]));
	}

	// Convert the first frame
	this->loadFrame(0u);
}

// Load a specific frame
void Image::loadFrame(UINT index) {
	if (index >= this->frameCount) return;

	HR;
	Mwrl::ComPtr<IWICFormatConverter> wicConverter;
	CHECK_WIN32API_EXCEPT(this->wicFactory->CreateFormatConverter(&wicConverter));
	CHECK_WIN32API_EXCEPT(wicConverter->Initialize(
		this->frames[index].Get(),
		GUID_WICPixelFormat32bppPBGRA, // BGRA is optimize by Windows, Direct2D need this format
		WICBitmapDitherTypeNone, nullptr, 0.0f, WICBitmapPaletteTypeCustom
	));

	// Get frame dimensions
	CHECK_WIN32API_EXCEPT(this->frames[index]->GetSize(&this->width, &this->height));

	// Allocate buffer
	UINT stride = this->width * 4;
	UINT bufferSize = stride * this->height;
	this->pBuffer = std::make_unique<BYTE[]>(bufferSize);

	// Copy frame pixels
	CHECK_WIN32API_EXCEPT(wicConverter->CopyPixels(nullptr, stride, bufferSize, this->pBuffer.get()));
}

// Advance to next frame (for GIF animation)
void Image::nextFrame() {
	this->currentFrameIndex = (this->currentFrameIndex + 1) % this->frameCount;
	loadFrame(this->currentFrameIndex);
}

UINT Image::getWidth() const noexcept {
	return this->width;
}

UINT Image::getHeight() const noexcept {
	return this->height;
}

BYTE* Image::getData() const noexcept {
	return this->pBuffer.get();
}

// Inverse the image by the horizontal axis
void Image::inverse() noexcept {
	UINT stride = this->width * 4;  // Nombre d'octets par ligne (BGRA, 4 octets par pixel)
	UINT halfHeight = this->height / 2;
	BYTE* pPixels = this->pBuffer.get();

	for (UINT y = 0; y < halfHeight; y++) {
		// Pointeurs vers les lignes à échanger
		UINT* pLine1 = reinterpret_cast<UINT*>(pPixels + stride * y);
		UINT* pLine2 = reinterpret_cast<UINT*>(pPixels + stride * (this->height - 1 - y));

		// Échange par pixels (UINT = 4 octets, donc 1 pixel)
		for (UINT x = 0; x < this->width; x++) {
			std::swap(pLine1[x], pLine2[x]);
		}
	}
}
