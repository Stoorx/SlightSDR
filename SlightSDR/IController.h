#pragma once

#include <string>
#include "IView.h"

class IController {
public:
	// App environment
	// Returns path to application
	virtual const std::wstring& getApplicationPath() const = 0;
	// Returns view object
	virtual const IView& getView() const = 0;

	// Commands
	// Play
	virtual void Play() = 0;
	// Stop
	virtual void Stop() = 0;
};