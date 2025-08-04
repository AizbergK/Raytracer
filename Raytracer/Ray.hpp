#ifndef _RAY_
#define _RAY_

#include <utility>
#include <vector>

#include "Tuples.hpp"
#include "Sphere.hpp"
#include "Intersection.hpp"
#include "Matrix.hpp"
#include "World.hpp"
#include "CompData.hpp"

class world;

class ray {
public:
	tuple m_origin;
	tuple m_direction;
	std::vector<intersection> m_intersections;

	ray() = default;
	ray(tuple, tuple);
	~ray() = default;

	tuple position(float);
	void intersect(sphere&);
	void intersect(world&);
	std::pair<tuple, tuple> transform(mat4x4&);
	intersection hit();
	void add_intersection(intersection&);
	comp_data get_comp_data();
};

#endif
