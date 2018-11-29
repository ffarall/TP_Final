#pragma once
#include "Settlement.h"
class City :
	public Settlement
{
public:
	City();
	City(string coordinate_);
	virtual ~City();

	virtual string whatAmI();
};

