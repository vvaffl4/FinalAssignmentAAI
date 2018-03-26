#ifndef UTILS
#define UTILS

#include <cmath>

inline bool isEqual(double a, double b)
{
	if (fabs(a - b) < 1E-12)
	{
		return true;
	}

	return false;
}

#endif