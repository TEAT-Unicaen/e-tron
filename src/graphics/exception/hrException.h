#pragma once


#include "../utils/setUpWindows.h"
#include "../../utils/eTronException.h"

#include <sstream>
#include <memory>


class HrException : public ETronException {
public:
	HrException(int line, const char* file, HRESULT hr) noexcept;
	const char* what() const noexcept override;
	virtual const char* getType() const noexcept override;
	static std::string translateErrorCode(HRESULT hr) noexcept;
	HRESULT getErrorCode() const noexcept;
	std::string getDescription() const noexcept;
private:
	HRESULT hr;
};
#define HR HRESULT hr
#define HR_EXCEPT(hr) HrException(__LINE__, __FILE__, hr)

#define CHECK_WIN32API_EXCEPT(hrcall) if (FAILED(hr = (hrcall))) throw HR_EXCEPT(hr)