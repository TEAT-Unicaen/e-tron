#pragma once

#include <exception>
#include <string>
#include <sstream>

class TronException : public std::exception {
public:
	TronException(int line, const char* file) noexcept;
	const char* what() const noexcept override;
	virtual const char* getType() const noexcept;
	int getLine() const noexcept;
	const std::string& getFile() const noexcept;
	std::string getLocationInString() const noexcept;

private:
	int line;
	std::string file;
protected:
	mutable std::string whatBuffer;
};

#define TRON_EXCEPT(hr) TronException(__LINE__, __FILE__, hr)