#ifndef _MATHUTILS_H_
#define _MATHUTILS_H_

#include "Matrix/Matrix2x2.h"
#include "Matrix/Matrix4x4.h"
#include "Vector/Vector2.h"
#include "Vector/Vector3.h"
#include "Vector/Vector4.h"

#define PI 3.1415926535897932
#define RADIAN 0.01745329251994329576923690768489

typedef Vector4<float> vec4;
typedef Vector3<float> vec3;
typedef Vector2 vec2;
typedef Matrix4x4<float> mat44;
typedef Matrix2x2 mat22;

namespace Math
{
	float radian(float degree);
	float degree(float radian);
}

#endif //_MATHUTILS_H_