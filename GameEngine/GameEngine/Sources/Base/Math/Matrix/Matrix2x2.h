#ifndef _MATRIX2X2_H_
#define _MATRIX2X2_H_

#include <iostream>

struct Vector2;
struct Matrix2x2
{
	//Matrix2x2(void);
	~Matrix2x2(void);
	Matrix2x2(const float element);
	Matrix2x2(const float member1 = 0, const float member2 = 0,
		const float member3 = 0, const float member4 = 0);
	Matrix2x2(const Matrix2x2& rhs);

	Matrix2x2& operator=(const Matrix2x2& rhs);

	Matrix2x2 operator+(const Matrix2x2& rhs) ;
	Matrix2x2 operator*(const Matrix2x2& rhs) ;
	Vector2 operator*(const Vector2& rhs) ;
	Matrix2x2 operator-(const Matrix2x2& rhs) ;

	Matrix2x2 operator+(const float constant) ;
	Matrix2x2 operator-(const float constant) ;
	Matrix2x2 operator*(const float constant) ;
	Matrix2x2 operator/(const float constant) ;

	Matrix2x2 Transpose(void);
	void SetIdentity(void);

	friend Matrix2x2 operator+(float constant, Matrix2x2& rhs);

	friend Matrix2x2 operator*(float constant, Matrix2x2& rhs);

	friend std::ostream& operator<<(std::ostream& os, const Matrix2x2& contents);

	float m_member[2][2];
};

#endif // _MATRIX2X2_H_