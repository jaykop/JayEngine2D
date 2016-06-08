#include "Vector2.h"

Vector2::~Vector2(void)
{}

Vector2::Vector2(float _x, float _y)
:x(_x), y(_y)
{}

Vector2::Vector2(const Vector2& copy)
{
	if (this != &copy)
	{
		x = copy.x;
		y = copy.y;
	}
}

Vector2& Vector2::operator=(const Vector2& rhs)
{
	if (this != &rhs)
	{
		x = rhs.x;
		y = rhs.y;
	}

	return *this;
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
	x += rhs.x;
	y += rhs.y;

	return *this;
}

Vector2& Vector2::operator+=(const float constant)
{
	x += constant;
	y += constant;

	return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;

	return *this;
}

Vector2& Vector2::operator-=(const float constant)
{
	x -= constant;
	y -= constant;

	return *this;
}
Vector2& Vector2::operator*=(const float constant)
{
	x *= constant;
	y *= constant;

	return *this;
}

Vector2 Vector2::operator+(const float constant)
{
	Vector2 new_one;

	new_one.x = x + constant;
	new_one.y = y + constant;

	return new_one;
}

Vector2 Vector2::operator+(const Vector2& rhs)
{
	Vector2 new_one;

	new_one.x = x + rhs.x;
	new_one.y = y + rhs.y;

	return new_one;
}

Vector2 Vector2::operator-(const float constant)
{
	Vector2 new_one;

	new_one.x = x - constant;
	new_one.y = y - constant;

	return new_one;
}

Vector2 Vector2::operator-(const Vector2& rhs)
{
	Vector2 new_one;

	new_one.x = x - rhs.x;
	new_one.y = y - rhs.y;

	return new_one;
}

Vector2 Vector2::operator*(const float constant)
{
	Vector2 new_one;

	new_one.x = x * constant;
	new_one.y = y * constant;

	return new_one;
}

Vector2 Vector2::operator/(const float constant)
{
	Vector2 new_one;

	new_one.x = x / constant;
	new_one.y = y / constant;

	return new_one;
}

float Vector2::Length(void) const
{
	return sqrt(x*x + y*y);
}

float Vector2::DotProduct(const Vector2& rhs)
{
	return x * rhs.x + y * rhs.y;
}

Vector2 Vector2::CrossProduct(const Vector2& rhs)
{
	return x * rhs.y - y * rhs.x;
}

Vector2 Vector2::Normalize(void)
{
	Vector2 result(x, y);
	result = result / Length();
	return result;
}


//Friend function
Vector2 operator+(float constant, Vector2& rhs)
{
	Vector2 new_one;

	new_one = rhs + constant;

	return new_one;
}

Vector2 operator*(float constant, Vector2& rhs)
{
	Vector2 new_one;

	new_one = rhs * constant;

	return new_one;
}

std::ostream& operator<<(std::ostream& os, const Vector2& constents)
{
	os << "Vector2[ " << constents.x << ", " << constents.y << " ]\n";
	return os;
}