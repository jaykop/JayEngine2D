#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include <iostream>

struct Vector2
{
	Vector2(float _x = 0, float _y = 0);
	Vector2(const Vector2& copy);
	~Vector2(void);

	Vector2& operator=(const Vector2& rhs);
	Vector2& operator+=(const Vector2& rhs);
	Vector2& operator+=(const float constant);
	Vector2& operator-=(const Vector2& rhs);
	Vector2& operator-=(const float constant);
	Vector2& operator*=(const float constant);

	Vector2 operator+(const float constant);
	Vector2 operator+(const Vector2& rhs);

	Vector2 operator-(const float constant);
	Vector2 operator-(const Vector2& rhs);

	Vector2 operator*(const float constant);
	Vector2 operator/(const float constant);

	float Length(void) const;
	float DotProduct(const Vector2& rhs);
	Vector2 CrossProduct(const Vector2& rhs);
	Vector2 Normalize(void);

	friend Vector2 operator+(float constant, Vector2& rhs);

	friend Vector2 operator*(float constant, Vector2& rhs);

	friend std::ostream& operator<<(std::ostream& os, const Vector2& constents);

	float x, y;
};

#endif // _VECTOR_H_