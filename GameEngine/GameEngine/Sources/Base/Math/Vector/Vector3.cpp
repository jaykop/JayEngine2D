#include "Vector4.h"
#include <cmath>

template <typename Type>
Vector3<Type>::~Vector3(void)
{}

template<typename Type>
Vector3<Type>::Vector3(Type _x, Type _y, Type _z)
: x(_x), y(_y), z(_z)
{}

template <typename Type>
Vector3<Type>::Vector3(const Vector3<Type>& copy)
{
	if (this != &copy)
	{
		x = copy.x;
		y = copy.y;
		z = copy.z;
	}
}

template <typename Type>
Vector3<Type>::Vector3(const Vector4<Type>& copy)
{
	x = copy.x;
	y = copy.y;
	z = copy.z;
}

template <typename Type>
Vector3<Type>& Vector3<Type>::operator=(const Vector3& rhs)
{
	if (this != &rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
	}

	return *this;
}

template <typename Type>
Vector3<Type>& Vector3<Type>::operator-(void)
{
	x = -x;
	y = -y;
	z = -z;

	return *this;
}

template <typename Type>
Vector3<Type> Vector3<Type>::operator+(const Type& constant) const
{
	Vector3 new_one;

	new_one.x = x + constant;
	new_one.y = y + constant;
	new_one.z = z + constant;

	return new_one;
}

template <typename Type>
Vector3<Type> Vector3<Type>::operator+(const Vector3& rhs) const
{
	Vector3 new_one;

	new_one.x = x + rhs.x;
	new_one.y = y + rhs.y;
	new_ont.z = z + rhs.z;

	return new_one;
}

template <typename Type>
Vector3<Type> Vector3<Type>::operator-(const Type& constant) const
{
	Vector3 new_one;

	new_one.x = x - constant;
	new_one.y = y - constant;
	new_one.z = z - constant;

	return new_one;
}

template <typename Type>
Vector3<Type> Vector3<Type>::operator-(const Vector3& rhs) const
{
	Vector3 new_one;

	new_one.x = x - rhs.x;
	new_one.y = y - rhs.y;
	new_one.z = z - rhs.z;

	return new_one;
}

template <typename Type>
Vector3<Type> Vector3<Type>::operator*(const Type& constant) const
{
	Vector3 new_one;

	new_one.x = x * constant;
	new_one.y = y * constant;
	new_one.z = z * constant;

	return new_one;
}

template <typename Type>
Vector3<Type> Vector3<Type>::operator/(const Type& constant) const
{
	Vector3 new_one;

	new_one.x = x / constant;
	new_one.y = y / constant;
	new_one.z = z / constant;

	return new_one;
}

template <typename Type>
Vector3<Type> operator+(Type constant, const Vector3<Type>& rhs)
{
	Vector3<Type> new_one;

	new_one = rhs + constant;

	return new_one;
}

template <typename Type>
Vector3<Type> operator*(Type constant, const Vector3<Type>& rhs)
{
	Vector3<Type> new_one;

	new_one = rhs * constant;

	return new_one;
}

template <typename Type>
std::ostream& operator<<(std::ostream& os, const Vector3<Type>& constents)
{
	os << "Vector3[ " << constents.x << ", " << constents.y << ", " << constents.z << " ]\n";
	return os;
}

template <typename Type>
Type Vector3<Type>::DotProduct(const Vector3& rhs)
{
	return x * rhs.x + y * rhs.y + z * rhs.z;
}

template <typename Type>
Vector3<Type> Vector3<Type>::CrossProduct(const Vector3& rhs)
{
	Vector3 result;

	result.x = y * rhs.z - z * rhs.y;
	result.y = z * rhs.x - x * rhs.z;
	result.z = x * rhs.y - y * rhs.x;

	return result;
}

template <typename Type>
Vector3<Type>& Vector3<Type>::operator+=(const Vector3& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

template <typename Type>
Vector3<Type>& Vector3<Type>::operator+=(const Type& constant)
{
	x += constant;
	y += constant;
	z += constant;

	return *this;
}

template <typename Type>
Vector3<Type>& Vector3<Type>::operator-=(const Vector3& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

template <typename Type>
Vector3<Type>& Vector3<Type>::operator-=(const Type& constant)
{
	x -= constant;
	y -= constant;
	z -= constant;

	return *this;
}

template <typename Type>
Vector3<Type>& Vector3<Type>::operator*=(const Type& constant)
{
	x *= constant;
	y *= constant;
	z *= constant;

	return *this;
}

template <typename Type>
Vector3<Type> Vector3<Type>::Normalize(void)
{
	Vector3 result(x,y,z);
	if (!Length())
		return vec3();

	result = result / Length();
	return result;
}

template <typename Type>
Type Vector3<Type>::Length(void) const
{
	return sqrt(x*x + y*y + z*z);
}

template <typename Type>
Vector3<Type> Vector3<Type>::Absolute(void)
{
	Vector3 result = Vector3<Type>(x,y,z);

	if (x < 0)
		result.x = -result.x;
	if (y < 0)
		result.y = -result.y;
	if (z < 0)
		result.z = -result.z;

	return result;
}