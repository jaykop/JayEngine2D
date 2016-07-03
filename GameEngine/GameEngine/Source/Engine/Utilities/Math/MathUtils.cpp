/******************************************************************************/
/*!
\file   MathUtils.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains MathUtils's class and member function

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "MathUtils.h"
#include <cmath>
#include <iomanip>

namespace Math
{
	/******************************************************************************/
	/*!
	\brief - Convert degree to radian 
	\param degree - to be converted
	\return result
	*/
	/******************************************************************************/
	float DegToRad(float degree)
	{
		float result = degree * static_cast<float>(RADIAN);
		return result;
	}

	/******************************************************************************/
	/*!
	\brief - Convert radian to degree
	\param radian - to be converted
	\return result
	*/
	/******************************************************************************/
	float RadToDeg(float radian)
	{
		float result = radian * static_cast<float>(RADIAN_DEGREE);
		return result;
	}

	/******************************************************************************/
	/*!
	\brief - Get Rotated point around specific pivot point
	\param point - point to be rotated
	\param angle - rotate degree
	\param pivot - pivot point
	\return new_point
	*/
	/******************************************************************************/
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

	/******************************************************************************/
	/*!
	\brief - Get a intersection point by two lines
	\param line1 - 1st line
	\param line2 - 2nd line
	\return inter_point
	*/
	/******************************************************************************/
	Pointf  IntersectPointOf2Lines(const Linef& line1, const Linef& line2)
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

	/******************************************************************************/
	/*!
	\brief - Check if two line is intersected or not; for lines.
	\param line1 - 1st line
	\param line2 - 2nd line
	\return bool
	*/
	/******************************************************************************/
	bool LineIntersection(const Linef& line1, const Linef& line2)
	{
		float denominator = ((line1.p2.x - line1.p1.x) * (line2.p2.y - line2.p1.y)) - ((line1.p2.y - line1.p1.y) * (line2.p2.x - line2.p1.x));
		float numerator1 = ((line1.p1.y - line2.p1.y) * (line2.p2.x - line2.p1.x)) - ((line1.p1.x - line2.p1.x) * (line2.p2.y - line2.p1.y));
		float numerator2 = ((line1.p1.y - line2.p1.y) * (line1.p2.x - line1.p1.x)) - ((line1.p1.x - line2.p1.x) * (line1.p2.y - line1.p1.y));

		if (!denominator) return numerator1 == 0 && numerator2 == 0;
		float r = numerator1 / denominator;
		float s = numerator2 / denominator;

		return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);

	}

	/******************************************************************************/
	/*!
	\brief - Get a intersection point by two lines
	\param line1 - 1st line's staring point(vector)
	\param line2 - 2nd line's staring point(vector)
	\param line1 - 1st line's ending point(vector)
	\param line2 - 2nd line's ending point(vector)
	\return boolVec
	*/
	/******************************************************************************/
	boolVec  IntersectPointOf2Lines(
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

	/******************************************************************************/
	/*!
	\brief - Check if two line is intersected or not; for vectors.
	\param line1 - 1st line's staring point(vector)
	\param line2 - 2nd line's staring point(vector)
	\param line1 - 1st line's ending point(vector)
	\param line2 - 2nd line's ending point(vector)
	\return bool
	*/
	/******************************************************************************/
	bool LineIntersection(
		const vec3& line1_start, const vec3& line1_end,
		const vec3& line2_start, const vec3& line2_end)
	{
		float denominator = ((line1_end.x - line1_start.x) * (line2_end.y - line2_start.y)) - ((line1_end.y - line1_start.y) * (line2_end.x - line2_start.x));
		float numerator1 = ((line1_start.y - line2_start.y) * (line2_end.x - line2_start.x)) - ((line1_start.x - line2_start.x) * (line2_end.y - line2_start.y));
		float numerator2 = ((line1_start.y - line2_start.y) * (line1_end.x - line1_start.x)) - ((line1_start.x - line2_start.x) * (line1_end.y - line1_start.y));

		if (!denominator) return numerator1 == 0 && numerator2 == 0;
		float r = numerator1 / denominator;
		float s = numerator2 / denominator;

		return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
	}

	/******************************************************************************/
	/*!
	\brief - Calculate the distance of two vector(point).
	\param line1 - 1st point(vector)
	\param line2 - 2nd point(vector)
	\return distance
	*/
	/******************************************************************************/
	float DistanceOf2Points(const vec3& a, const vec3& b)
	{
		vec3 square((b.x - a.x) * (b.x - a.x), (b.y - a.y) * (b.y - a.y), 0);
		return sqrt(square.x + square.y);
	}

	/******************************************************************************/
	/*!
	\brief - Calculate the distance of two point.
	\param line1 - 1st point
	\param line2 - 2nd point
	\return distance
	*/
	/******************************************************************************/
	float DistanceOf2Points(const Pointf& a, const Pointf& b)
	{
		vec3 square((b.x - a.x) * (b.x - a.x), (b.y - a.y) * (b.y - a.y), 0);
		return sqrt(square.x + square.y);
	}

	/******************************************************************************/
	/*!
	\brief - Calculate the distance of point and segment.
	\param point
	\param line_start
	\param line_end
	\return distance
	*/
	/******************************************************************************/
	float DistanceOfPointSegment(const vec3& point, const vec3& line_start, const vec3& line_end)
	{
		// segment is nit a segment; a point
		float length = DistanceOf2Points(line_start, line_end);
		if (!length)
			return DistanceOf2Points(line_start, point);

		// Unless...
		float projection = ((point.x - line_start.x) * (line_end.x - line_start.x) + 
			(point.y - line_start.y) * (line_end.y - line_start.y)) / length;

		//
		//	1st case		2nd case		3rd case
		//		*				*				*
		//		   A						 B
		//			=========================
		
		// 1st case
		if (projection < 0) return DistanceOf2Points(line_start, point);
		// 3rd case
		else if (projection > length) return DistanceOf2Points(line_end, point);
		// 2nd case
		else return abs((point.y - line_start.y) * (line_end.x - line_start.x)
			- (point.x - line_start.x) * (line_end.y - line_start.y)) / length;
	}
	
	/******************************************************************************/
	/*!
	\brief - Calculate the distance of point and segment.
	\param point
	\param line
	\return distance
	*/
	/******************************************************************************/
	float DistanceOfPointSegment(const Pointf& point, const Linef& line)
	{
		// segment is nit a segment; a point
		float length = DistanceOf2Points(line.p1, line.p2);
		if (!length)
			return DistanceOf2Points(line.p1, point);

		// Unless...
		float projection = ((point.x - line.p1.x) * (line.p2.x - line.p1.x) +
			(point.y - line.p1.y) * (line.p2.y - line.p1.y)) / length;

		//
		//	1st case		2nd case		3rd case
		//		*				*				*
		//		   A						 B
		//			=========================

		// 1st case
		if (projection < 0) return DistanceOf2Points(line.p1, point);
		// 3rd case
		else if (projection > length) return DistanceOf2Points(line.p2, point);
		// 2nd case
		else return abs((point.x - line.p1.x) * (line.p2.y - line.p1.y) +
			(point.y - line.p1.y) * (line.p2.x - line.p1.x)) / length;
	}
}