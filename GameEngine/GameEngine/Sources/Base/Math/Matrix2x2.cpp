#include "Matrix2x2.h"
#include "Vector2.h"

//Matrix2x2::Matrix2x2(void)
//{}
Matrix2x2::~Matrix2x2(void)
{}
Matrix2x2::Matrix2x2(const float element)
{
	for (int i = 0; i < 2; ++i)
	for (int j = 0; j < 2; ++j)
		m_member[i][j] = element;
}

Matrix2x2::Matrix2x2(const float member1, const float member2,
	const float member3, const float member4)
{
	m_member[0][0] = member1;
	m_member[0][1] = member2;
	m_member[1][0] = member3;
	m_member[1][1] = member4;
}

Matrix2x2::Matrix2x2(const Matrix2x2& rhs)
{
	if (this != &rhs)
	{
		for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			m_member[i][j] = rhs.m_member[i][j];
	}
}

Matrix2x2& Matrix2x2::operator=(const Matrix2x2& rhs)
{
	if (this != &rhs)
	{
		for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			m_member[i][j] = rhs.m_member[i][j];
	}

	return *this;
}

Matrix2x2 Matrix2x2::operator+(const Matrix2x2& rhs) 
{
	Matrix2x2 result;

	for (int i = 0; i < 2; ++i)
	for (int j = 0; j < 2; ++j)
		m_member[i][j] = m_member[i][j] + rhs.m_member[i][j];

	return result;
}

Matrix2x2 Matrix2x2::operator*(const Matrix2x2& rhs) 
{
	Matrix2x2 result;

	result.m_member[0][0] = m_member[0][0] * rhs.m_member[0][0] + m_member[0][1] * rhs.m_member[1][0];
	result.m_member[0][1] = m_member[0][0] * rhs.m_member[0][1] + m_member[0][1] * rhs.m_member[1][1];
	result.m_member[1][0] = m_member[1][0] * rhs.m_member[0][0] + m_member[1][1] * rhs.m_member[1][0];
	result.m_member[1][1] = m_member[1][0] * rhs.m_member[0][1] + m_member[1][1] * rhs.m_member[1][1];

	return result;
}

Vector2 Matrix2x2::operator*(const Vector2& rhs) 
{
	Vector2 result;

	result.x = m_member[0][0] * rhs.x + m_member[0][1] * rhs.y ;
	result.y = m_member[1][0] * rhs.x + m_member[1][1] * rhs.y ;

	return result;
}

Matrix2x2 Matrix2x2::operator-(const Matrix2x2& rhs) 
{
	Matrix2x2 result;

	for (int i = 0; i < 2; ++i)
	for (int j = 0; j < 2; ++j)
		m_member[i][j] = m_member[i][j] - rhs.m_member[i][j];

	return result;
}

Matrix2x2 Matrix2x2::operator+(const float constant) 
{
	Matrix2x2 result;

	for (int i = 0; i < 2; ++i)
	for (int j = 0; j < 2; ++j)
		result.m_member[i][j] = m_member[i][j] + constant;

	return result;
}

Matrix2x2 Matrix2x2::operator-(const float constant) 
{
	Matrix2x2 result;

	for (int i = 0; i < 2; ++i)
	for (int j = 0; j < 2; ++j)
		result.m_member[i][j] = m_member[i][j] - constant;

	return result;
}

Matrix2x2 Matrix2x2::operator*(const float constant) 
{
	Matrix2x2 result;

	for (int i = 0; i < 2; ++i)
	for (int j = 0; j < 2; ++j)
		result.m_member[i][j] = m_member[i][j] * constant;

	return result;
}

Matrix2x2 Matrix2x2::operator/(const float constant) 
{
	Matrix2x2 result;

	for (int i = 0; i < 2; ++i)
	for (int j = 0; j < 2; ++j)
		result.m_member[i][j] = m_member[i][j] / constant;

	return result;
}

Matrix2x2 Matrix2x2::Transpose(void)
{
	Matrix2x2 result;

	result.m_member[0][0] = m_member[0][0];
	result.m_member[0][1] = m_member[1][0];
	result.m_member[1][0] = m_member[0][1];
	result.m_member[1][1] = m_member[1][1];

	return result;
}

void Matrix2x2::SetIdentity(void) 
{
	m_member[0][0] = 1;
	m_member[0][1] = 0;
	m_member[1][0] = 0;
	m_member[1][1] = 1;
}

//Friend function
Matrix2x2 operator+(float constant, Matrix2x2& rhs) 
{
	Matrix2x2 result;
	result = rhs + constant;
	return result;
}

Matrix2x2 operator*(float constant, Matrix2x2& rhs) 
{
	Matrix2x2 result;
	result = rhs * constant;
	return result;
}

std::ostream& operator<<(std::ostream& os, const Matrix2x2& contents)
{
	for (int i = 0; i < 2; ++i)
	{
		os << "[ ";
		for (int j = 0; j < 2; ++j)
		{
			os.setf(std::ios_base::showpoint);
			os << contents.m_member[i][j] << " ";
		}
		os << "]\n";
	}

	return os;
}