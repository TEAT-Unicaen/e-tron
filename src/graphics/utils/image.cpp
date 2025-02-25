#include "image.h"

Image::Image(const std::wstring path) {
	HR;
	// Create the WIC factory
	Mwrl::ComPtr<IWICImagingFactory> wicFactory;
	CHECK_WIN32API_EXCEPT(CoCreateInstance(
		CLSID_WICImagingFactory, // The ID of the WIC factory
		nullptr,
		CLSCTX_INPROC_SERVER, // Execute in the same process
		IID_PPV_ARGS(&wicFactory)
	));

	// Load the image
	Mwrl::ComPtr<IWICBitmapDecoder> wicDecoder;
	CHECK_WIN32API_EXCEPT(wicFactory->CreateDecoderFromFilename(
		path.c_str(), // The filename
		nullptr, // No need to specify the desired vendor
		GENERIC_READ, // Read permission
		WICDecodeMetadataCacheOnLoad, // Cache the metadata
		&wicDecoder
	));

	// Get the dimensions of the image
	Mwrl::ComPtr<IWICBitmapFrameDecode> wicFrame;
	CHECK_WIN32API_EXCEPT(wicDecoder->GetFrame(0, wicFrame.GetAddressOf()));
	CHECK_WIN32API_EXCEPT(wicFrame->GetSize(&this->width, &this->height));
	
	// Coversions
	Mwrl::ComPtr<IWICFormatConverter> wicConverter;
	CHECK_WIN32API_EXCEPT(wicFactory->CreateFormatConverter(&wicConverter));
	CHECK_WIN32API_EXCEPT(wicConverter->Initialize(
		wicFrame.Get(), // The frame to convert
		GUID_WICPixelFormat32bppPRGBA, // RBGA format
		WICBitmapDitherTypeNone, // No dithering
		nullptr,
		0.0f, // Alpha transparency
		WICBitmapPaletteTypeCustom // Custom palette
	));

	// Get the image data
	UINT stride = this->width * 4;// Bytes per row (4 is for each pixel)
	UINT bufferSize = stride * this->height;
	this->pBuffer = std::make_unique<BYTE[]>(bufferSize);
	CHECK_WIN32API_EXCEPT(wicConverter->CopyPixels(
		nullptr,
		stride,
		bufferSize,
		this->pBuffer.get()
	));
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
