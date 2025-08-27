#ifndef _INTERSECTION_
#define _INTERSECTION_

#include "Shapes.hpp"

class Intersection {
public:
	double m_time = NAN;
	Shape* m_obj = nullptr;

	Intersection() = default;
	Intersection(double, Shape*);
	Intersection(std::pair<double, Shape*>);
	~Intersection() = default;

	bool operator==(Intersection& other);
};

#endif
