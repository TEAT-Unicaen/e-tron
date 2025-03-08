#pragma once

#include "../../../../utils/eTronException.h"
#include <vector>
#include <string>
#include <sstream>

class InfoOnlyException : public ETronException {
public:
	InfoOnlyException(int line, const char* file, std::vector<std::string> infoDescriptions) noexcept;
	const char* what() const noexcept override;
	const char* getType() const noexcept override;
	std::string getInfoDescription() const noexcept;
private:
	std::string infoDescriptions;
};
#define INFO_ONLY_EXCEPT(v) InfoOnlyException(__LINE__, __FILE__, v)