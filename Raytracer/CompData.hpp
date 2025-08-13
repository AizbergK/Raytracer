#ifndef _COMPDATA_
#define _COMPDATA_

#include "Tuples.hpp"
#include "Intersection.hpp"

class CompData {
public:
	double n1 = 1.0;
	double n2 = 1.0;
	Intersection intersection;
	Point4 pt;
	Point4 over_pt;
	Point4 under_pt;
	Vector4 eyev;
	Vector4 normalv;
	Vector4 reflectv;
	bool is_inside = false;
};

#endif