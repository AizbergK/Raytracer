#include "Tuples.hpp"

TestTuple::TestTuple() : Tuple4<TestTuple>(0.0, 0.0, 0.0, 0.0) {}
TestTuple::TestTuple(double X, double Y, double Z, double W) : Tuple4<TestTuple>(X, Y, Z, W) {}

Point4::Point4() : Tuple4<Point4>(0.0, 0.0, 0.0, 1.0) {}
Point4::Point4(double X, double Y, double Z) : Tuple4<Point4>(X, Y, Z, 1.0) {}

Vector4::Vector4() : Tuple4<Vector4>(0.0, 0.0, 0.0, 0.0) {}
Vector4::Vector4(double X, double Y, double Z) : Tuple4<Vector4>(X, Y, Z, 0.0) {}

Color4::Color4() : Tuple4<Color4>(0.0, 0.0, 0.0, 0.0) {}


//=== POINT === 
Point4 Point4::operator+(const Vector4& other) const
{
	Point4 result;

	result.x = x + other.x;
	result.y = y + other.y;
	result.z = z + other.z;

	return result;
}

Point4 Point4::operator-(const Vector4& other) const
{
	Point4 result;

	result.x = x - other.x;
	result.y = y - other.y;
	result.z = z - other.z;

	return result;
}

Vector4 Point4::operator-(const Point4& other) const
{
	Vector4 result;

	result.x = x - other.x;
	result.y = y - other.y;
	result.z = z - other.z;

	return result;
}

//=== VECTOR === 
Point4 Vector4::point_at(double t)
{
	return Point4{ this->x * t, this->y * t, this->z * t };
}

//=== COLOR === 
Color4 Color4::saturate(double lower, double upper)
{
	Color4 res{ this->x, this->y, this->z };
	if (res.x < lower) res.x = lower;
	if (res.x > upper) res.x = upper;

	if (res.y < lower) res.y = lower;
	if (res.y > upper) res.y = upper;

	if (res.z < lower) res.z = lower;
	if (res.z > upper) res.z = upper;

	return res;
}


double magnitude(const Vector4& vect)
{
	return sqrt(pow(vect.x, 2.0) + pow(vect.y, 2.0) + pow(vect.z, 2.0));
}

Vector4 normalize(const Vector4& vect)
{
	double mag = magnitude(vect);
	return Vector4{ vect.x / mag, vect.y / mag, vect.z / mag };
}

double dot(const Vector4& lhs, const Vector4& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

Vector4 cross(const Vector4& lhs, const Vector4& rhs)
{
	return Vector4{ lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x };
}

Vector4 hadamard(const Vector4& lhs, const Vector4& rhs)
{
	return Vector4{ lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z };
}

Color4 hadamard(const Color4& lhs, const Color4& rhs)
{
	return Color4{ lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z };
}

Vector4 reflect(const Vector4& eye, const Vector4& nm)
{
	double d2 = 2 * dot(eye, nm);
	return Vector4{ eye.x - nm.x * d2, eye.y - nm.y * d2, eye.z - nm.z * d2 };
}