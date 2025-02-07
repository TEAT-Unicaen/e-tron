#include "hrException.h"

HrException::HrException(int line, const char* file, HRESULT hr) noexcept
	: ETronException(line, file), hr(hr) {}

const char* HrException::what() const noexcept {
	std::ostringstream oss;
	oss << this->getType() << std::endl
		<< "Error Code : 0x" << std::hex << std::uppercase << this->getErrorCode() << std::dec << " (" << (unsigned long)this->getErrorCode() << ")" << std::endl
		<< "Description :" << this->getDescription() << std::endl
		<< getLocationInString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* HrException::getType() const noexcept {
	return "Tron Window Exception";
}

std::string HrException::translateErrorCode(HRESULT hr) noexcept {
	char* pMsgBuf = nullptr;
	// Ask windows to give us the string version of this error code
	const DWORD nMsgLen = FormatMessage(
		// alocate the message         | search from system         | remove the inserting things
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&pMsgBuf), 0, nullptr
	);
	if (nMsgLen == 0) {
		return "Unidentified error code";
	}
	std::string errorString = pMsgBuf;
	LocalFree(pMsgBuf);// FormatMessage uses malloc, so we have to free it
	return errorString;
}

HRESULT HrException::getErrorCode() const noexcept {
	return this->hr;
}

std::string HrException::getDescription() const noexcept {
	return translateErrorCode(this->hr);
}