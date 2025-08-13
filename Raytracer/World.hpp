#ifndef _WORLD_
#define _WORLD_

#include <vector>
#include <memory>

#include "Shapes.hpp"
#include "PointLight.hpp"
#include "CompData.hpp"
#include "Ray.hpp"

class World {
public:
	std::vector<std::shared_ptr<Shape>> m_shapes;
	std::vector<Light> m_point_lights;

	void add_light(Light&);
	void add_object(Shape&);
	Color4 shade_hit(CompData&, int remaining_hits);
};

Color4 color_at(World&, Ray&, int remaining_hits);
Color4 reflected_color(World&, CompData&, int remaining_hits);
Color4 refracted_color(World&, CompData&, int remaining_hits);
double schlick(CompData&);

World default_world();

bool is_shadowed(World&, Point4&, Light&);
void intersect(World&, Ray&);
#endif