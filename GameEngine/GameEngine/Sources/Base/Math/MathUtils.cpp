#include "MathUtils.h"
#include <cmath>

namespace Math
{
	float DegToRad(float degree)
	{
		float result = degree * static_cast<float>(RADIAN);
		return result;
	}

	float RadToDeg(float radian)
	{
		float result = radian * static_cast<float>(RADIAN_DEGREE);
		return result;
	}
}