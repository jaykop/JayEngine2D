//TO DO: Change Vector4 to Vector4

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>

template <typename Type>
class Vector3;

//Vector4
template <typename Type>
class Vector4
{
public:

	//Vector4(void);
	~Vector4(void);
	Vector4(Type _x = 0, Type _y = 0, Type _z = 0, Type _w = 0);
	Vector4(const Vector4<Type>& rhs);
	Vector4(Vector3<Type> vec, Type _w = 0);

	Vector4& operator=(const Vector4& rhs);
	Vector4& operator+=(const Vector4& rhs);
	Vector4& operator+=(const Type& constant);
	Vector4& operator-=(const Vector4& rhs);
	Vector4& operator-=(const Type& constant);
	Vector4& operator*=(const Type& constant);

	Vector4 operator+(const Vector4& rhs) ;
	Vector4 operator+(const Type& constant) ;

	Vector4 operator-(const Vector4& rhs) ;
	Vector4 operator-(const Type& constant) ;

	Vector4 operator*(const Type& constant) ;
	Vector4 operator/(const Type& constant);

	Type Length(void) const;
	Type DotProduct(const Vector4& rhs);
	Vector4<Type> Normalize(void);

	template <typename Type>
	friend Vector4<Type> operator+(Type constant, Vector4<Type>& rhs);

	template <typename Type>
	friend Vector4<Type> operator*(Type constant, Vector4<Type>& rhs);
	
	template <typename Type>
	friend std::ostream& operator<<(std::ostream& os, const Vector4<Type>& contents);

	Type x, y, z, w;

private:
	
};

#include "Vector4.cpp"

#endif // _MATRIX_H_