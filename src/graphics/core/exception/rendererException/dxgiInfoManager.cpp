#include "dxgiInfoManager.h"

DxgiInfoManager::DxgiInfoManager() {
	// signature of DXGIGetDebugInterface for loading the DXGI debug DLL
	typedef HRESULT(WINAPI* DXGIGetDebugInterface)(REFIID, void**);

	// Load the DXGI debug DLL
	const auto hModDxgiDebug = LoadLibraryEx("dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
	if (hModDxgiDebug == nullptr) {
		throw RENDERER_LAST_EXCEPT_NO_INFO();
	}
	// Get address of DXGIGetDebugInterface and store it in a function pointer
	const auto dxgiGetDebugInterface = reinterpret_cast<DXGIGetDebugInterface>(
		reinterpret_cast<void*>(GetProcAddress(hModDxgiDebug, "DXGIGetDebugInterface"))
	);
	if (dxgiGetDebugInterface == nullptr) {
		throw RENDERER_LAST_EXCEPT_NO_INFO();
	}

	// Get the DXGI info queue
	HR;
	CHECK_RENDERER_EXCEPT_NO_INFO(dxgiGetDebugInterface(IID_PPV_ARGS(&this->pDxgiInfoQueue)));
}

DxgiInfoManager::~DxgiInfoManager() {
	if (this->pDxgiInfoQueue != nullptr) {
		this->pDxgiInfoQueue->Release();
	}
}

void DxgiInfoManager::updateTheStartingPointIndex() noexcept {
	//set the new starting point to the current number of messages
	this->newStartingPointIndex = this->pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);	
}

std::vector<std::string> DxgiInfoManager::getMessages() const {
	// get the number of new messages from the current starting point
	std::vector<std::string> messages;
	const auto end = this->pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
	for (auto i = this->newStartingPointIndex; i < end; i++) {
		HR;
		SIZE_T messageLength = 0;
		// get the size of message i in bytes
		CHECK_RENDERER_EXCEPT_NO_INFO(this->pDxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, nullptr, &messageLength));
		// allocate memory for message
		auto bytes = std::make_unique<byte[]>(messageLength);
		DXGI_INFO_QUEUE_MESSAGE* pMessage = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());
		// get the message and push his description into the vector
		CHECK_RENDERER_EXCEPT_NO_INFO(this->pDxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, pMessage, &messageLength));
		messages.emplace_back(pMessage->pDescription);
	}
	return messages;
}