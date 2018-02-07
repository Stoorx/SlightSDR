#pragma once

#include <string>

class IController {
public:
	// App environment
	// Returns path to application
	virtual const std::wstring& getApplicationPath() const = 0;
};