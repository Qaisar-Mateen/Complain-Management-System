#pragma once
#define NOMINMAX
#include <windows.h>

class Person {
public:
	virtual int getID() const = 0;
	virtual void control() = 0;
};

