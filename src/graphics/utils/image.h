#pragma once

#include "setUpWindows.h"
#include <wincodec.h>
#include <wrl/client.h>

#include "../core/exception/hrException.h"

namespace Mwrl = Microsoft::WRL;

class Image {
public:
	Image() = delete;
	Image(const std::wstring path);
	~Image() = default;

	UINT getWidth() const noexcept;
	UINT getHeight() const noexcept;
	BYTE* getData() const noexcept;
private:
	UINT width;
	UINT height;
	std::unique_ptr<BYTE[]> pBuffer;
};