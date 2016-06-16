#ifndef _MATHUTILS_H_
#define _MATHUTILS_H_

#include "Matrix/Matrix2x2.h"
#include "Matrix/Matrix4x4.h"
#include "Vector/Vector2.h"
#include "Vector/Vector3.h"
#include "Vector/Vector4.h"

#define PI 3.1415926535897932
#define RADIAN 0.01745329251994329576923690768489
#define RADIAN_DEGREE 57.2958

typedef Vector4<float> vec4;
typedef Vector3<float> vec3;
typedef Vector2 vec2;
typedef Matrix4x4<float> mat44;
typedef Matrix2x2 mat22;

namespace Math
{
	struct Pointf
	{
		float x;
		float y;
	};

	struct Linef
	{
		Pointf p1;
		Pointf p2;
	};

	struct boolVec
	{
		bool boolean;
		vec3 vector;
	};

	float DegToRad(float degree);
	float RadToDeg(float radian);

	Pointf Rotation(const Pointf& point, float angle, const Pointf& pivot);
	Pointf IntersectPointOf2Lines(const Linef& line1, const Linef& line2);
	bool LineIntersection(const Linef& line1, const Linef& line2);

	boolVec  IntersectPointOf2Lines(
		const vec3& line1_start, const vec3& line1_end,
		const vec3& line2_start, const vec3& line2_end);

	bool LineIntersection(
		const vec3& line1_start, const vec3& line1_end,
		const vec3& line2_start, const vec3& line2_end);
}

#endif //_MATHUTILS_H_