#ifndef _WORLD_
#define _WORLD_

#include <vector>
#include <concepts>

#include "Shapes.hpp"
#include "PointLight.hpp"
#include "CompData.hpp"
#include "Ray.hpp"

class World {
public:
	std::vector<Shape*> m_shapes;
	std::vector<Light> m_point_lights;

	void delete_objects();
	void add_light(Light&);

	template<std::derived_from<Shape> T>
	inline void add_object(T& shape);
	template<std::derived_from<Shape> T>
	inline void add_object(T* shape);

	Color4 shade_hit(CompData&, int remaining_hits);
};

template<std::derived_from<Shape> T>
inline void World::add_object(T& shape)
{
	T* node = new T(shape);
	m_shapes.emplace_back(node);
	Group::track_nodes.emplace_back(node);
}
template<std::derived_from<Shape> T>
inline void World::add_object(T* shape)
{
	m_shapes.emplace_back(shape);
	Group::track_nodes.emplace_back(shape);
}

Color4 color_at(World&, Ray&, int remaining_hits);
Color4 reflected_color(World&, CompData&, int remaining_hits);
Color4 refracted_color(World&, CompData&, int remaining_hits);
double schlick(CompData&);

World default_world();

bool is_shadowed(World&, Point4&, Light&);
void intersect(World&, Ray&);
#endif