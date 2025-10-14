#pragma once

#include "GameDefines.h"

class IInput {
public:
	virtual void Input(const eInput input) = 0;
};