#ifndef _TUPLES_
#define _TUPLES_
#include "Helpers.hpp"

class Vector4;
class Point4;
class Color4;
class TestTuple;

template <typename Derived>
class Tuple4 {
public:
	double x, y, z, w;

	Tuple4() = default;
	constexpr Tuple4(double X, double Y, double Z, double W) : x{ X }, y{ Y }, z{ Z }, w{ W } {}
	~Tuple4() = default;

	void operator=(const Derived& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
	}

	bool operator==(const Derived& other) const
	{
		return is_equal(x, other.x) && is_equal(y, other.y) && is_equal(z, other.z) && is_equal(w, other.w);
	}

	Derived operator+(const Derived& other) const
	{
		Derived result;

		result.x = x + other.x;
		result.y = y + other.y;
		result.z = z + other.z;
		result.w = w + other.w;

		return result;
	}

	Derived operator+=(Derived& other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		this->w += other.w;

		return *this;
	}

	Derived operator-(const Derived& other) const
	{
		Derived result;

		result.x = x - other.x;
		result.y = y - other.y;
		result.z = z - other.z;
		result.w = w - other.w;

		return result;
	}

	Derived operator*(double factor) const
	{
		Derived result;

		result.x = x * factor;
		result.y = y * factor;
		result.z = z * factor;
		result.w = w * factor;

		return result;
	}

	Derived friend operator*(double lhs, const Derived& rhs)
	{
		return rhs * lhs;
	}

	Derived operator/(double factor) const
	{
		Derived result;

		result.x = x / factor;
		result.y = y / factor;
		result.z = z / factor;
		result.w = w / factor;

		return result;
	}

	Derived operator-()
	{
		Derived result;

		result.x = -x;
		result.y = -y;
		result.z = -z;
		result.w = -w;

		return result;
	}
};

class Color4 : public Tuple4<Color4> {
public:
	using Tuple4<Color4>::operator==; //Needed for gtest <--
	Color4();
	constexpr Color4(double R, double G, double B) : Tuple4<Color4>(R, G, B, 0.0) {}

	Color4 saturate(double lower, double upper);
};

class Point4 : public Tuple4<Point4> {
public:
	using Tuple4<Point4>::operator==;
	Point4();
	Point4 (double X, double Y, double Z);
	Vector4 operator-(const Point4&) const;
	Point4 operator+(const Vector4&) const;
	Point4 operator-(const Vector4&) const;

};

class Vector4 : public Tuple4<Vector4> {
public:
	using Tuple4<Vector4>::operator==;
	Vector4();
	Vector4 (double X, double Y, double Z);
	Point4 point_at(double t);
};

//unit test class
class TestTuple : public Tuple4<TestTuple> {
public:
	using Tuple4<TestTuple>::operator==;
	TestTuple();
	TestTuple(double X, double Y, double Z, double W);
};


double magnitude(const Vector4&);
Vector4 normalize(const Vector4&);

double dot(const Vector4&, const Vector4&);
Vector4 cross(const Vector4&, const Vector4&);
Vector4 hadamard(const Vector4&, const Vector4&);
Color4 hadamard(const Color4&, const Color4&);

Vector4 reflect(const Vector4&, const Vector4&);

constexpr Color4 BLACK{ 0.0, 0.0, 0.0 };
constexpr Color4 WHITE{ 1.0, 1.0, 1.0 };

#endif