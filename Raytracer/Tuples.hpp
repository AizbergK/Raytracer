#ifndef _TUPLES_
#define _TUPLES_

#include <cstdlib>
#include <cmath>

#include "Helpers.hpp"

class tuple {
public:


	tuple() = default;
	tuple(float X, float Y, float Z, float W);
	~tuple() = default;

	void operator=(const tuple&);
	bool operator==(const tuple&) const;
	tuple operator+(const tuple&) const;
	tuple operator+=(const tuple&);
	tuple operator-(const tuple&) const;
	tuple operator*(float) const;
	tuple operator/(float) const;
	tuple operator-();
	tuple friend operator*(float, const tuple&);

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 0.0f;

	tuple point_at(float);
	tuple saturate(float lower, float upper) const;
};

float magnitude(const tuple&);
tuple normalize(const tuple&);

float dot(const tuple&, const tuple&);
tuple cross(const tuple&, const tuple&);
tuple hadamard(const tuple&, const tuple&);

tuple point(float, float, float);
tuple vector(float, float, float);
tuple color(float, float, float);

bool is_point(const tuple&);
bool is_vector(const tuple&);

tuple reflect(const tuple&, const tuple&);


#endif