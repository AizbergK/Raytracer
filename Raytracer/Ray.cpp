#include "Ray.hpp"

ray::ray(tuple pt, tuple dir) : m_origin{ pt }, m_direction{ dir } {}

tuple ray::position(float time) 
{
	return m_origin + time * m_direction;
}

void ray::intersect(sphere& sph)
{
	intersection i1, i2;

	auto inv = sph.m_transform.inverse();
	auto tr = this->transform(inv);

	tuple sph_to_ray = tr.first - sph.m_position;

	float a = dot(tr.second, tr.second);
	float b = 2 * dot(tr.second, sph_to_ray);
	float c = dot(sph_to_ray, sph_to_ray) - sph.m_radius * sph.m_radius;

	float delta = b * b - 4 * a * c;
	if (delta < 0) return;

	i1.m_time = ( - b - std::sqrt(delta)) / (2 * a);
	i1.m_obj = &sph;

	i2.m_time = ( - b + std::sqrt(delta)) / (2 * a);
	i2.m_obj = &sph;

	m_intersections.emplace_back(i1);
	m_intersections.emplace_back(i2);
}

void ray::intersect(world& the_world)
{
	for (auto& sp : the_world.m_spheres)
	{
		this->intersect(sp);
	}
}

std::pair<tuple, tuple> ray::transform(mat4x4& trmat)
{
	return std::pair<tuple, tuple>(trmat * this->m_origin, trmat * this->m_direction);
}

intersection ray::hit()
{
	intersection the_hit;
	the_hit.m_time = INFINITY;

	for (auto& i : m_intersections)
		if (i.m_time >= 0.0f && the_hit.m_time > i.m_time)
			the_hit = i;

	return the_hit;
}

void ray::add_intersection(intersection& inter)
{
	m_intersections.emplace_back(inter);
}

comp_data ray::get_comp_data()
{
	comp_data result;

	result.inter = this->hit();
	result.pt = this->position(result.inter.m_time);
	result.eyev = -this->m_direction;
	result.normalv = result.inter.m_obj->normal_at(result.pt);
	if (dot(result.eyev, result.normalv) < 0.0f)
	{
		result.is_inside = true;
		result.normalv = -result.normalv;
	}

	return result;
}