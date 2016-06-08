#include "MathUtils.h"
#include <cmath>

namespace Math
{
	float radian(float degree)
	{
		float result = degree * static_cast<float>(RADIAN);
		return result;
	}

	float degree(float radian)
	{
		float result = radian * static_cast<float>(PI);
		return result;
	}
}