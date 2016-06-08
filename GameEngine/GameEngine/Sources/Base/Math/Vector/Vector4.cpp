#include "Vector4.h"
#include "Vector3.h"

//template <typename Type>
//Vector4<Type>::Vector4(void)
//:x(0), y(0), z(0), w(0)
//{}

template <typename Type>
Vector4<Type>::~Vector4(void)
{}

template <typename Type>
Vector4<Type>::Vector4(Type _x, Type _y, Type _z, Type _w)
:x(_x), y(_y), z(_z), w(_w)
{}

template <typename Type>
Vector4<Type>::Vector4(Vector3<Type> vec, Type _w)
: x(vec.x), y(vec.y), z(vec.z), w(_w)
{}

template <typename Type>
Vector4<Type>::Vector4(const Vector4<Type>& rhs)
{
	if (this != &rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
	}
}

template <typename Type>
Vector4<Type>& Vector4<Type>::operator=(const Vector4<Type>& rhs)
{
	if (this != &rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
	}

	return *this;
}

template <typename Type>
Vector4<Type> Vector4<Type>::operator+(const Vector4<Type>& rhs)
{
	Vector4 result;

	result.x = x + rhs.x;
	result.y = y + rhs.y;
	result.z = z + rhs.z;
	result.w = w + rhs.w;

	return result;
}

template <typename Type>
Vector4<Type> Vector4<Type>::operator+(const Type& constant) 
{
	Vector4 result;

	result.x = x + constant;
	result.y = y + constant;
	result.z = z + constant;
	result.w = w + constant;

	return result;
}

template <typename Type>
Vector4<Type> Vector4<Type>::operator-(const Vector4<Type>& rhs)
{
	Vector4 result;

	result.x = x - rhs.x;
	result.y = y - rhs.y;
	result.z = z - rhs.z;
	result.w = w - rhs.w;

	return result;
}

template <typename Type>
Vector4<Type> Vector4<Type>::operator-(const Type& constant)
{
	Vector4 result;

	result.x = x - constant;
	result.y = y - constant;
	result.z = z - constant;
	result.w = w - constant;

	return result;
}

template <typename Type>
Vector4<Type> Vector4<Type>::operator*(const Type& constant)
{
	Vector4 result;

	result.x = x * constant;
	result.y = y * constant;
	result.z = z * constant;
	result.w = w * constant;

	return result;
}

template <typename Type>
Vector4<Type> Vector4<Type>::operator / (const Type& constant)
{
	Vector4 result;

	result.x = x / constant;
	result.y = y / constant;
	result.z = z / constant;
	result.w = w / constant;

	return result;
}

template <typename Type>
Vector4<Type> operator+(Type constant, Vector4<Type>& rhs)
{
	Vector4<Type> result;
	
	result = rhs + constant;

	return result;
}

template <typename Type>
Vector4<Type> operator*(Type constant, Vector4<Type>& rhs)
{
	Vector4<Type> result;
	
	result = rhs * constant;

	return result;
}

template <typename Type>
std::ostream& operator<<(std::ostream& os, const Vector4<Type>& contents)
{
	os << "Vector4[ " << constents.x << ", " << constents.y << ", " << constents.z << ", " << constents.w << " ]\n";
	return os;
}

template <typename Type>
Type Vector4<Type>::DotProduct(const Vector4& rhs)
{
	Type result = x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
	return result;
}

template <typename Type>
Vector4<Type>& Vector4<Type>::operator+=(const Vector4& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;

	return *this;
}

template <typename Type>
Vector4<Type>& Vector4<Type>::operator+=(const Type& constant)
{
	x += constant;
	y += constant;
	z += constant;
	w += constant;

	return *this;
}

template <typename Type>
Vector4<Type>& Vector4<Type>::operator-=(const Vector4& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;

	return *this;
}

template <typename Type>
Vector4<Type>& Vector4<Type>::operator-=(const Type& constant)
{
	x -= constant;
	y -= constant;
	z -= constant;
	w -= constant;

	return *this;
}

template <typename Type>
Vector4<Type>& Vector4<Type>::operator*=(const Type& constant)
{
	x *= constant;
	y *= constant;
	z *= constant;
	w += constant;

	return *this;
}

template <typename Type>
Vector4<Type> Vector4<Type>::Normalize(void)
{
	Vector4 result(x, y, z, w);
	Type length = sqrt(x*x + y*y + z*z + w*w);
	result = result / length;
	return result;
}

template <typename Type>
Type Vector4<Type>::Length(void) const
{
	return sqrt(x*x + y*y + z*z + w*w);
}