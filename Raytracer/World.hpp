#ifndef _WORLD_
#define _WORLD_

#include <vector>

#include "Sphere.hpp"
#include "PointLight.hpp"
#include "CompData.hpp"
#include "Ray.hpp"

class ray;

class world {
public:
	std::vector<sphere> m_spheres;
	std::vector<pt_lght> m_point_lights;

	void add_light(pt_lght);
	void add_object(sphere);
	tuple shade_hit(comp_data);
};

tuple color_at(world&, ray&);
world default_world();

#endif