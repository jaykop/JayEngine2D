#ifndef _MATRIX4X4_H_
#define _MATRIX4X4_H_

template <typename Type>
class Vector3;

template <typename Type>
class Vector4;

//Matrix 4x4
template <typename Type>
class Matrix4x4
{
public:
	Matrix4x4(void);
	~Matrix4x4(void);
	Matrix4x4(const Type& element);
	Matrix4x4(const Vector4<Type> member);
	Matrix4x4(Vector4<Type> member1, Vector4<Type> member2,
		Vector4<Type> member3, Vector4<Type> member4);
	Matrix4x4(const Matrix4x4& rhs);

	Matrix4x4& operator=(const Matrix4x4& rhs);
	Matrix4x4& operator-(void);

	Matrix4x4 operator+(const Matrix4x4& rhs) const;
	Matrix4x4 operator*(const Matrix4x4& rhs) const;
	Vector4<Type> operator*(const Vector4<Type>& rhs) const;
	Matrix4x4 operator-(const Matrix4x4& rhs) const;

	Matrix4x4 operator+(const Type& constant) const;
	Matrix4x4 operator-(const Type& constant) const;
	Matrix4x4 operator*(const Type& constant) const;
	Matrix4x4 operator/(const Type& constant) const;

	Matrix4x4 Transpose(void);
	void SetIdentity(void);

	static Matrix4x4<Type> Ortho(float left, float right, float top, float bottom, float zNear, float zFar);
	static Matrix4x4<Type> Perspective(float fovy, float aspectRatio, float zNear, float zFar);
	static Matrix4x4<Type> LookAt(Vector3<Type> eye, Vector3<Type> look, Vector3<Type> up);
	static Matrix4x4<Type> Translate(const Vector3<Type>& vec);
	static Matrix4x4<Type> Scale(const Vector3<Type>& vec);
	static Matrix4x4<Type> Rotate(float degree, Vector3<Type> vec);

	template <typename Type>
	friend Matrix4x4<Type> operator+(Type constant, const Matrix4x4<Type>& rhs);

	template <typename Type>
	friend Matrix4x4<Type> operator*(Type constant, const Matrix4x4<Type>& rhs);

	template <typename Type>
	friend std::ostream& operator<<(std::ostream& os, const Matrix4x4<Type>& contents);

	Type m_member[4][4];

private:
	
};

#include "Matrix4x4.cpp"

#endif // _MATRIX4X4_H_
