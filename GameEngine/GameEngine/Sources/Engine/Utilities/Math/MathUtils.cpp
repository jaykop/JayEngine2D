#include "MathUtils.h"
#include <cmath>

namespace Math
{
	//Convert degree to radian 
	float DegToRad(float degree)
	{
		float result = degree * static_cast<float>(RADIAN);
		return result;
	}

	//Convert radian to degree
	float RadToDeg(float radian)
	{
		float result = radian * static_cast<float>(RADIAN_DEGREE);
		return result;
	}
}