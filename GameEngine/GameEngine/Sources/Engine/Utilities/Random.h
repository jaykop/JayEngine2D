#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <cstdlib>
#include "Math\MathUtils.h"

class Random
{

public:

	float GetRandomFloat(float left = FLT_MIN, float right = FLT_MAX)
	{	
		float result = left + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (right - left)));
		return result;
	};

	int	GetRandomInt(int left = INT_MIN, int right = INT_MAX)
	{
		int result = rand() % right + left;
		return result;
	};

	vec3 GetRandomVector(float left = FLT_MIN, float right = FLT_MAX)
	{
		vec3 result;
		result.x = left + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (right - left)));
		result.y = left + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (right - left)));
		result.z = left + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (right - left)));

		return result;
	}

	static Random& GetInstance(void)
	{
		static Random random;
		return random;
	}

private:

	Random(void){
		//Set seed
		srand((unsigned)clock());
	};
};

#endif // _RANDOM_H_