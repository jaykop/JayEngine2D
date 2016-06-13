#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <cstdlib>
#include "Math\MathUtils.h"

class Random
{

public:

	float GetRandomFloat(float left = 0.f, float right = 1.f)
	{	
		float result = left + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (right - left)));
		return result;
	};

	int	GetRandomInt(int left = 0, int right = 100)
	{
		int result = rand() % right + left;
		return result;
	};

	vec3 GetRandomVector(float left = 0.f, float right = 1.f)
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