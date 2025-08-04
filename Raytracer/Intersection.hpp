#ifndef _INTERSECTION_
#define _INTERSECTION_

#include "Sphere.hpp"

class intersection {
public:
	float m_time = NAN;
	sphere* m_obj = nullptr;

	intersection() = default;
	intersection(float, sphere&);
	~intersection() = default;
};

#endif
