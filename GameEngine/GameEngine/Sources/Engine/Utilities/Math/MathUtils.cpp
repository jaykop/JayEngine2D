#include "MathUtils.h"
#include <cmath>
#include <iomanip>

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

	//Get Rotated point around specific pivot point
	Pointf Rotation(const Pointf& point, float angle, const Pointf& pivot)
	{
		Pointf new_point(point);

		float s = sinf(Math::DegToRad(angle));
		float c = cosf(Math::DegToRad(angle));

		new_point.x -= pivot.x;
		new_point.y -= pivot.y;

		float new_x = point.x * c - point.y * s;
		float new_y = point.x * s + point.y * c;

		new_point.x = new_x + pivot.x;
		new_point.y = new_y + pivot.y;

		return new_point;
	}

	//Get a intersection point by two lines
	Pointf  IntersectOf2Lines(const Linef& line1, const Linef& line2)
	{
		//Get Coefficients
		float a2 = line2.p2.y - line2.p1.y;
		float b2 = line2.p1.x - line2.p2.x;
		float c2 = line2.p2.x * line2.p1.y - line2.p1.x * line2.p2.y;

		float a1 = line1.p2.y - line1.p1.y;
		float b1 = line1.p1.x - line1.p2.x;
		float c1 = line1.p2.x * line1.p1.y - line1.p1.x * line1.p2.y;

		//Check if they are parallel
		float D = a1 * b2 - a2 * b1;
		if (!D)
		{
			//Todo: Do assert or warning!
		}

		Pointf inter_point{ (b1*c2 - b2*c1) / D, (a2*c1 - a1*c2) / D };

		return inter_point;
	}

	//Get a intersection point by two lines
	boolVec  IntersectOf2Lines(
		const vec3& line1_start, const vec3& line1_end,
		const vec3& line2_start, const vec3& line2_end)
	{
		//Get Coefficients
		float a2 = line2_end.y - line2_start.y;
		float b2 = line2_start.x - line2_end.x;
		float c2 = line2_end.x * line2_start.y - line2_start.x * line2_end.y;

		float a1 = line1_end.y - line1_start.y;
		float b1 = line1_start.x - line1_end.x;
		float c1 = line1_end.x * line1_start.y - line1_start.x * line1_end.y;

		//Check if they are parallel
		float D = a1 * b2 - a2 * b1;
		if (D)
		{
			vec3 inter_point{ (b1*c2 - b2*c1) / D, (a2*c1 - a1*c2) / D };
			return boolVec{ true, inter_point };
		}

		//Invalid return
		return boolVec{ false, vec3() };
	}
}