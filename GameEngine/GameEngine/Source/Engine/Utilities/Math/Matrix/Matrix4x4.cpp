/******************************************************************************/
/*!
\file   Matrix4x4.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Matrix4x4's template class and member function
Custom Matrix looks like this...

		  0  1  2  3
	0	[ 00 10 20 30 ]
	1	[ 01 11 21 31 ]
	2	[ 02 12 22 32 ]
	3	[ 03 13 23 33 ]

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "../Vector/Vector3.h"
#include "../Vector/Vector4.h"
#include "Matrix4x4.h"

/******************************************************************************/
/*!
\brief - Matrix4x4 Constructor
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type>::Matrix4x4(void)
{
	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < 4; ++j)
		m_member[i][j] = 0;
}

/******************************************************************************/
/*!
\brief - Matrix4x4 Destructor
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type>::~Matrix4x4(void)
{}

/******************************************************************************/
/*!
\brief - Matrix4x4 Constructor
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type>::Matrix4x4(const Type& element)
{
	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < 4; ++j)
		m_member[i][j] = element;
}

/******************************************************************************/
/*!
\brief - Matrix4x4 Copy Constructor
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type>::Matrix4x4(const Matrix4x4<Type>& rhs)
{
	if (this != &rhs)
	{
		for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			m_member[i][j] = rhs.m_member[i][j];
	}
}

/******************************************************************************/
/*!
\brief - Matrix4x4 = operator 
\param rhs - matrix to assign
\return *this
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type>& Matrix4x4<Type>::operator = (const Matrix4x4<Type>& rhs)
{
	if (this != &rhs)
	{
		for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			m_member[i][j] = rhs.m_member[i][j];
	}

	return *this;
}

/******************************************************************************/
/*!
\brief - Matrix4x4 - unary operator
\return *this
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type>& Matrix4x4<Type>::operator-(void)
{
	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < 4; ++j)
		m_member[i][j] = -m_member[i][j];

	return *this;
}

/******************************************************************************/
/*!
\brief - Matrix4x4 + operator
\param rhs - matrix to add
\return result
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::operator + (const Matrix4x4<Type>& rhs) const
{
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < 4; ++j)
		m_member[i][j] = m_member[i][j] + rhs.m_member[i][j];

	return result;
}

/******************************************************************************/
/*!
\brief - Matrix4x4 + operator
\param rhs - number to add
\return result
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::operator + (const Type& constant) const
{
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < 4; ++j)
		result.m_member[i][j] = m_member[i][j] + constant;

	return result;
}

/******************************************************************************/
/*!
\brief - Matrix4x4 - operator
\param rhs - matrix to subtract
\return result
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::operator - (const Matrix4x4<Type>& rhs) const
{
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < 4; ++j)
		result.m_member[i][j] = m_member[i][j] - rhs.m_member[i][j];

	return result;
}

/******************************************************************************/
/*!
\brief - Matrix4x4 - operator
\param rhs - number to subtract
\return result
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::operator - (const Type& constant) const
{
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < 4; ++j)
		result.m_member[i][j] = m_member[i][j] - constant;

	return result;
}

/******************************************************************************/
/*!
\brief - Matrix4x4 * operator
\param rhs - number to multiply
\return result
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::operator * (const Type& constant) const
{
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < 4; ++j)
		result.m_member[i][j] = m_member[i][j] * constant;

	return result;
}

/******************************************************************************/
/*!
\brief - Matrix4x4 * operator
\param rhs - matrix to multiply
\return result
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::operator*(const Matrix4x4<Type>& rhs) const
{
	Matrix4x4 result;

	result.m_member[0][0] = m_member[0][0] * rhs.m_member[0][0] + m_member[0][1] * rhs.m_member[1][0] + m_member[0][2] * rhs.m_member[2][0] + m_member[0][3] * rhs.m_member[3][0];
	result.m_member[0][1] = m_member[0][0] * rhs.m_member[0][1] + m_member[0][1] * rhs.m_member[1][1] + m_member[0][2] * rhs.m_member[2][1] + m_member[0][3] * rhs.m_member[3][1];
	result.m_member[0][2] = m_member[0][0] * rhs.m_member[0][2] + m_member[0][1] * rhs.m_member[1][2] + m_member[0][2] * rhs.m_member[2][2] + m_member[0][3] * rhs.m_member[3][2];
	result.m_member[0][3] = m_member[0][0] * rhs.m_member[0][3] + m_member[0][1] * rhs.m_member[1][3] + m_member[0][2] * rhs.m_member[2][3] + m_member[0][3] * rhs.m_member[3][3];

	result.m_member[1][0] = m_member[1][0] * rhs.m_member[0][0] + m_member[1][1] * rhs.m_member[1][0] + m_member[1][2] * rhs.m_member[2][0] + m_member[1][3] * rhs.m_member[3][0];
	result.m_member[1][1] = m_member[1][0] * rhs.m_member[0][1] + m_member[1][1] * rhs.m_member[1][1] + m_member[1][2] * rhs.m_member[2][1] + m_member[1][3] * rhs.m_member[3][1];
	result.m_member[1][2] = m_member[1][0] * rhs.m_member[0][2] + m_member[1][1] * rhs.m_member[1][2] + m_member[1][2] * rhs.m_member[2][2] + m_member[1][3] * rhs.m_member[3][2];
	result.m_member[1][3] = m_member[1][0] * rhs.m_member[0][3] + m_member[1][1] * rhs.m_member[1][3] + m_member[1][2] * rhs.m_member[2][3] + m_member[1][3] * rhs.m_member[3][3];

	result.m_member[2][0] = m_member[2][0] * rhs.m_member[0][0] + m_member[2][1] * rhs.m_member[1][0] + m_member[2][2] * rhs.m_member[2][0] + m_member[2][3] * rhs.m_member[3][0];
	result.m_member[2][1] = m_member[2][0] * rhs.m_member[0][1] + m_member[2][1] * rhs.m_member[1][1] + m_member[2][2] * rhs.m_member[2][1] + m_member[2][3] * rhs.m_member[3][1];
	result.m_member[2][2] = m_member[2][0] * rhs.m_member[0][2] + m_member[2][1] * rhs.m_member[1][2] + m_member[2][2] * rhs.m_member[2][2] + m_member[2][3] * rhs.m_member[3][2];
	result.m_member[2][3] = m_member[2][0] * rhs.m_member[0][3] + m_member[2][1] * rhs.m_member[1][3] + m_member[2][2] * rhs.m_member[2][3] + m_member[2][3] * rhs.m_member[3][3];

	result.m_member[3][0] = m_member[3][0] * rhs.m_member[0][0] + m_member[3][1] * rhs.m_member[1][0] + m_member[3][2] * rhs.m_member[2][0] + m_member[3][3] * rhs.m_member[3][0];
	result.m_member[3][1] = m_member[3][0] * rhs.m_member[0][1] + m_member[3][1] * rhs.m_member[1][1] + m_member[3][2] * rhs.m_member[2][1] + m_member[3][3] * rhs.m_member[3][1];
	result.m_member[3][2] = m_member[3][0] * rhs.m_member[0][2] + m_member[3][1] * rhs.m_member[1][2] + m_member[3][2] * rhs.m_member[2][2] + m_member[3][3] * rhs.m_member[3][2];
	result.m_member[3][3] = m_member[3][0] * rhs.m_member[0][3] + m_member[3][1] * rhs.m_member[1][3] + m_member[3][2] * rhs.m_member[2][3] + m_member[3][3] * rhs.m_member[3][3];

	return result;
}

/******************************************************************************/
/*!
\brief - Matrix4x4 * operator with vector4
\param rhs - vector4 to multiply
\return result
*/
/******************************************************************************/
template <typename Type>
Vector4<Type> Matrix4x4<Type>::operator*(const Vector4<Type>& rhs) const
{
	Vector4<Type> result;

	result.x = m_member[0][0] * rhs.x + m_member[0][1] * rhs.y + m_member[0][2] * rhs.z + m_member[0][3] * rhs.w;
	result.y = m_member[1][0] * rhs.x + m_member[1][1] * rhs.y + m_member[1][2] * rhs.z + m_member[1][3] * rhs.w;
	result.z = m_member[2][0] * rhs.x + m_member[2][1] * rhs.y + m_member[2][2] * rhs.z + m_member[2][3] * rhs.w;
	result.w = m_member[3][0] * rhs.x + m_member[3][1] * rhs.y + m_member[3][2] * rhs.z + m_member[3][3] * rhs.w;

	return result;
}

/******************************************************************************/
/*!
\brief - Matrix4x4 / operator 
\param rhs - number to divide
\return result
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::operator / (const Type& constant) const
{
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < 4; ++j)
		result.m_member[i][j] = m_member[i][j] / constant;

	return result;
}

/******************************************************************************/
/*!
\brief - Set matrix identity
*/
/******************************************************************************/
template <typename Type>
void Matrix4x4<Type>::SetIdentity(void)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (i == j)
				m_member[i][j] = 1;
			else
				m_member[i][j] = 0;
		}
	}
}

/******************************************************************************/
/*!
\brief - Friend function + operator
\param constant - number to add
\param rhs - this
\return result
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type> operator+(Type constant, const Matrix4x4<Type>& rhs)
{
	Matrix4x4<Type> result;

	result = rhs + constant;

	return result;
}

/******************************************************************************/
/*!
\brief - Friend function * operator
\param constant - number to multiply
\param rhs - this
\return result
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type> operator*(Type constant, const Matrix4x4<Type>& rhs)
{
	Matrix4x4<Type> result;
	result = rhs * constant;
	return result;
}

/******************************************************************************/
/*!
\brief - Friend function << operator
\param os - storage to put contents
\param contents - contents to print out
\return os
*/
/******************************************************************************/
template <typename Type>
std::ostream& operator<<(std::ostream& os, const Matrix4x4<Type>& contents)
{
	for (int i = 0; i < 4; ++i)
	{
		os << "[ ";
		for (int j = 0; j < 4; ++j)
		{
			os.setf(std::ios_base::showpoint);
			os << contents.m_member[i][j] << " ";
		}
		os << "]\n";
	}

	return os;
}

/******************************************************************************/
/*!
\brief - Transpose matrix
\return result
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::Transpose(void)
{
	Matrix4x4 result;

	result = *this;
	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < 4; ++j)
		result.m_member[j][i] = m_member[i][j];

	return result;
}

/******************************************************************************/
/*!
\brief - Make tanslate matrix
\param vec - position
\return result
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::Translate(const Vector3<Type>& vec)
{
	Matrix4x4 result;
	result.SetIdentity();

	result.m_member[3][0] = vec.x;
	result.m_member[3][1] = vec.y;
	result.m_member[3][2] = vec.z;

	return result;
}

/******************************************************************************/
/*!
\brief - Make scale matrix
\param vec - scale
\return result
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::Scale(const Vector3<Type>& vec)
{
	Matrix4x4 result;
	result.SetIdentity();

	result.m_member[0][0] = vec.x;
	result.m_member[1][1] = vec.y;
	result.m_member[2][2] = vec.z;

	return result;
}

/******************************************************************************/
/*!
\brief - Make tanslate matrix
\param degree - degree to rotate
\param vec - axis to rotate
\return result
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::Rotate(float degree, Vector3<Type> vec)
{
	float c = cos(degree);
	float s = sin(degree);

	//Matrix4x4 result;
	Matrix4x4 rotate;
	rotate.SetIdentity();

	Vector3<Type> axis = vec.Normalize();
	Vector3<Type> temp = ((Type(1) - c) * axis);

	rotate.m_member[0][0] = c + temp.x * axis.x;
	rotate.m_member[0][1] = temp.x * axis.y + s * axis.z;
	rotate.m_member[0][2] = temp.x * axis.z - s * axis.y;

	rotate.m_member[1][0] = temp.y * axis.x - s * axis.z;
	rotate.m_member[1][1] = c + temp.y * axis.y;
	rotate.m_member[1][2] = temp.y * axis.z + s * axis.x;

	rotate.m_member[2][0] = temp.z * axis.x + s * axis.y;
	rotate.m_member[2][1] = temp.z * axis.y - s * axis.x;
	rotate.m_member[2][2] = c + temp.z * axis.z;

	return rotate;
}

/******************************************************************************/
/*!
\brief - Make perspective matrix
\param fovy - Field of view by y
\param aspectRatio - aspect ratio
\param zNear - closest projection position
\param zFar - the most far projection position
\return result
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::Perspective(float fovy, float aspectRatio, float zNear, float zFar)
{
	Matrix4x4 result;
	Type tanHalfFovy = tanf(fovy / static_cast<Type>(2));

	result.m_member[0][0] = static_cast<Type>(1) / (aspectRatio * tanHalfFovy);
	result.m_member[1][1] = static_cast<Type>(1) / (tanHalfFovy);
	result.m_member[2][2] = -(zFar + zNear) / (zFar - zNear);
	result.m_member[2][3] = -static_cast<Type>(1);
	result.m_member[3][2] = -(static_cast<Type>(2) * zFar * zNear) / (zFar - zNear);

	return result;
}

/******************************************************************************/
/*!
\brief - Make orthogonal matrix
\param left - left screen side
\param right - right screen side
\param bottom - bottom screen side
\param top - top screen side
\param zNear - closest projection position
\param zFar - the most far projection position
\return result
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::Ortho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	Matrix4x4 result;

	result.m_member[0][0] = static_cast<Type>(2) / (right - left);
	result.m_member[1][1] = static_cast<Type>(2) / (top - bottom);
	result.m_member[2][2] = -static_cast<Type>(2) / (zFar - zNear);
	
	result.m_member[3][0] = -(right + left) / (right - left);
	result.m_member[3][1] = -(top + bottom) / (top - bottom);
	result.m_member[3][2] = -(zFar + zNear) / (zFar - zNear);
	result.m_member[3][3] = static_cast<Type>(1);

	return result;
}

/******************************************************************************/
/*!
\brief - Make LookAt matrix
\param eye - set row axis
\param look - set right axis
\param up - set up axis 
\return result
*/
/******************************************************************************/
template <typename Type>
Matrix4x4<Type> Matrix4x4<Type>::LookAt(Vector3<Type> eye, Vector3<Type> look, Vector3<Type> up)
{

	Matrix4x4 result;
	result.SetIdentity();
	Vector3<Type> F = (look - eye);

	Vector3<Type> f = F.Normalize();
	Vector3<Type> s = f.CrossProduct(up);
	Vector3<Type> u = s.CrossProduct(f);

	result.m_member[0][0] = s.x;
	result.m_member[1][0] = s.y;
	result.m_member[2][0] = s.z;

	result.m_member[0][1] = u.x;
	result.m_member[1][1] = u.y;
	result.m_member[2][1] = u.z;

	result.m_member[0][2] = -f.x;
	result.m_member[1][2] = -f.y;
	result.m_member[2][2] = -f.z;

	result.m_member[3][0] = -s.DotProduct(eye);
	result.m_member[3][1] = -u.DotProduct(eye);
	result.m_member[3][2] = f.DotProduct(eye);

	return result;
}