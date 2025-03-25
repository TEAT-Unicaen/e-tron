#pragma once

#include "setUpWindows.h"
#include <wincodec.h>
#include <wrl/client.h>
#include <vector>

#include "../core/exception/hrException.h"

namespace Mwrl = Microsoft::WRL;

class Image {
public:
	Image() = delete;
	Image(const std::wstring& path);
	~Image() = default;

	UINT getWidth() const noexcept;
	UINT getHeight() const noexcept;
	BYTE* getData() const noexcept;
	void inverse() noexcept;

	void nextFrame();
private:
	UINT width;
	UINT height;
	std::unique_ptr<BYTE[]> pBuffer;

	UINT frameCount = 1;
	UINT currentFrameIndex = 0;
	Mwrl::ComPtr<IWICImagingFactory> wicFactory;
	std::vector<Mwrl::ComPtr<IWICBitmapFrameDecode>> frames;

	void loadFrame(UINT index);
};