#pragma once

#include <exception>
#include <string>
#include <sstream>

class ETronException : public std::exception {
public:
	ETronException(int line, const char* file) noexcept;
	ETronException(int line, const char* file, const char* message) noexcept;
	const char* what() const noexcept override;
	virtual const char* getType() const noexcept;
	int getLine() const noexcept;
	const std::string& getFile() const noexcept;
	std::string getLocationInString() const noexcept;

private:
	int line;
	std::string file;
	std::string message;
protected:
	mutable std::string whatBuffer;
};

#define ETRON_EXCEPT(message) ETronException(__LINE__, __FILE__, message)