#ifndef _INTERSECTION_
#define _INTERSECTION_

#include "Shapes.hpp"

class Intersection {
public:
	double m_time = NAN;
	std::shared_ptr<Shape> m_obj = nullptr;

	Intersection() = default;
	Intersection(double, std::shared_ptr<Shape>);
	~Intersection() = default;

	bool operator==(Intersection& other);
};

#endif
