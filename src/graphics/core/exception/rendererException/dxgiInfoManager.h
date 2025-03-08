#pragma once

#include "../../../utils/setUpWindows.h"
#include "rendererHrException.h"

#include <memory>
#include <vector>
#include <string>
#include <dxgidebug.h>
#pragma comment(lib, "dxguid.lib")

class DxgiInfoManager {
public:
	DxgiInfoManager();
	~DxgiInfoManager();
	DxgiInfoManager(const DxgiInfoManager&) = delete;
	DxgiInfoManager& operator=(const DxgiInfoManager&) = delete;

	void updateTheStartingPointIndex() noexcept;
	std::vector<std::string> getMessages() const;

private:
	ULONGLONG newStartingPointIndex = 0u;
	IDXGIInfoQueue* pDxgiInfoQueue = nullptr;
};