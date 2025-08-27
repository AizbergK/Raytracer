#ifndef _RAY_
#define _RAY_

#include <algorithm>
#include <utility>
#include <vector>
#include <optional>

#include "Tuples.hpp"
#include "Shapes.hpp"
#include "Intersection.hpp"
#include "Matrix.hpp"
#include "CompData.hpp"
#include "PVpair.hpp"



class Ray {
public:
	PVpair m_origin_dir;
	std::vector<Intersection> m_intersections;

	Ray() = default;
	Ray(PVpair);
	~Ray() = default;

	Point4 position(double);
	void intersect(Shape*);
	
	PVpair get_pv();
	Intersection hit();
	void add_intersection(Intersection&);
	CompData get_comp_data(std::optional<int> opt = std::nullopt);
	Vector4 normal_at(CompData);
};

#endif
