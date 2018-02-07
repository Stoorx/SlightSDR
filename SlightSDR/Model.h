#pragma once


#include "IModel.h"

class Model : public IModel {
public:	
	Model() { a = 0xDEADBABA; }
private:
	int a;
};