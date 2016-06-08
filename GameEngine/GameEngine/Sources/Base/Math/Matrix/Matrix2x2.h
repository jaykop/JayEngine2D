#ifndef _MATRIX2X2_H_
#define _MATRIX2X2_H_

#include <iostream>

struct Vector2;
struct Matrix2x2
{
	//Matrix2x2(void);
	~Matrix2x2(void);
	Matrix2x2(const float element = 0);
	Matrix2x2(const float member1, const float member2,
		const float member3, const float member4);
	Matrix2x2(const Matrix2x2& rhs);

	Matrix2x2& operator=(const Matrix2x2& rhs);
	Matrix2x2& operator-(void);

	Matrix2x2 operator+(const Matrix2x2& rhs) const;
	Matrix2x2 operator*(const Matrix2x2& rhs) const;
	Vector2 operator*(const Vector2& rhs) const;
	Matrix2x2 operator-(const Matrix2x2& rhs) const;

	Matrix2x2 operator+(const float constant) const;
	Matrix2x2 operator-(const float constant) const;
	Matrix2x2 operator*(const float constant) const;
	Matrix2x2 operator/(const float constant) const;

	Matrix2x2 Transpose(void);
	void SetIdentity(void);

	friend Matrix2x2 operator+(float constant, const Matrix2x2& rhs);

	friend Matrix2x2 operator*(float constant, const Matrix2x2& rhs);

	friend std::ostream& operator<<(std::ostream& os, const Matrix2x2& contents);

	float m_member[2][2];
};

#endif // _MATRIX2X2_H_