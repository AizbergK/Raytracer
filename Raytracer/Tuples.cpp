#include "Tuples.hpp"

tuple::tuple(float X, float Y, float Z, float W) : x{ X }, y{ Y }, z{ Z }, w{ W } {}

void tuple::operator=(const tuple& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
}

bool tuple::operator==(const tuple& other) const
{
	return is_equal(x, other.x) && is_equal(y, other.y) && is_equal(z, other.z) && is_equal(w, other.w);
}

tuple tuple::operator+(const tuple& other) const
{
	tuple result;
	result.x += x + other.x;
	result.y += y + other.y;
	result.z += z + other.z;
	result.w += w + other.w;

	return result;
}

tuple tuple::operator+=(const tuple& other)
{
	*this = *this + other;
	return *this;
}

tuple tuple::operator-(const tuple& other) const
{
	tuple result;
	result.x += x - other.x;
	result.y += y - other.y;
	result.z += z - other.z;
	result.w += w - other.w;

	return result;
}

tuple tuple::operator*(float factor) const
{
	tuple result;
	result.x = x * factor;
	result.y = y * factor;
	result.z = z * factor;
	result.w = w * factor;
	
	return result;
}

tuple operator*(float lhs, const tuple& rhs)
{
	return rhs * lhs;
}

tuple tuple::operator/(float factor) const
{
	tuple result;
	result.x = x / factor;
	result.y = y / factor;
	result.z = z / factor;
	result.w = w / factor;

	return result;
}

tuple tuple::operator-()
{
	x = -x;
	y = -y;
	z = -z;
	w = -w;
	return *this;
}

tuple tuple::point_at(float t) 
{
	return *this * t;
}

tuple tuple::saturate(float lower, float upper) const
{
	tuple res{ *this };
	if (res.x < lower) res.x = lower;
	if (res.x > upper) res.x = upper;
		   			      
	if (res.y < lower) res.y = lower;
	if (res.y > upper) res.y = upper;
		   			      
	if (res.z < lower) res.z = lower;
	if (res.z > upper) res.z = upper;
		   			      
	if (res.w < lower) res.w = lower;
	if (res.w > upper) res.w = upper;

	return res;
}

float magnitude(const tuple& vect)
{
	return sqrt(pow(vect.x, 2.0f) + pow(vect.y, 2.0f) + pow(vect.z, 2.0f) + pow(vect.w, 2.0f));
}

tuple normalize(const tuple& vect)
{
	return vect / magnitude(vect);
}

float dot(const tuple& lhs, const tuple& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

tuple cross(const tuple& lhs, const tuple& rhs)
{
	return vector(	lhs.y * rhs.z - lhs.z * rhs.y, 
					lhs.z * rhs.x - lhs.x * rhs.z, 
					lhs.x * rhs.y - lhs.y * rhs.x);
}

tuple hadamard(const tuple& lhs, const tuple& rhs)
{ 
	return tuple(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
}

tuple reflect(const tuple& eye, const tuple& nm)
{
	return eye - nm * 2 * dot(eye, nm);
}

tuple point(float x, float y, float z) { return tuple(x, y, z, 1.0f); }
tuple vector(float x, float y, float z) { return tuple(x, y, z, 0.0f); }
tuple color(float x, float y, float z) { return tuple(x, y, z, 0.0f); }

bool is_point(const tuple& t) { return is_equal(t.w, 1.0f); }
bool is_vector(const tuple& t) { return is_equal(t.w, 0.0f); }