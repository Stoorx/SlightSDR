#pragma once

#include <stdint.h>

class IModel {
public:
	// Getters
	//virtual uint32_t getBaseFrequency() const = 0;
	
	// Setters
	//virtual void setBaseFrequency() = 0;
	enum class ModelStatement : uint32_t {
		Stop,
		Run
	};
};