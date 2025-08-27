#include "World.hpp"

void World::delete_objects()
{
	Group::delete_track_nodes();
}

void World::add_light(Light& lgth)
{
	m_point_lights.emplace_back(lgth);
}

//Recursive ray loop
Color4 World::shade_hit(CompData& comps, int remaining_hits)
{
	Color4 surface_color{ 0.0, 0.0, 0.0 };

	for(auto& light : m_point_lights)
	{
		bool in_shadow = is_shadowed(*this, comps.over_pt, light);
		surface_color = surface_color + lighting(
			comps.intersection, 
			light,
			comps.pt, 
			comps.eyev, 
			comps.normalv, 
			in_shadow
		);
	}

	Color4 reflect_color{ reflected_color(*this, comps, remaining_hits) };
	Color4 refract_color{ refracted_color(*this, comps, remaining_hits) };

	Material& mat = comps.intersection.m_obj->m_material;

	if (mat.m_reflective > 0.0 && mat.m_transparency > 0.0)
	{
		double reflectance = schlick(comps);
		return surface_color + reflect_color * reflectance + refract_color * (1.0 - reflectance);
	}

	return surface_color + reflect_color + refract_color;
}

Color4 reflected_color(World& w, CompData& cd, int remaining_hits)
{
	double reflect_coef = cd.intersection.m_obj->m_material.m_reflective;

	if (reflect_coef == 0.0 || remaining_hits == 0)
	{
		return BLACK;
	}

	Ray reflect_ray{ PVpair(cd.over_pt, cd.reflectv) };

	--remaining_hits;

	Color4 color{ color_at(w, reflect_ray, remaining_hits) };

	return color * reflect_coef;
}

Color4 refracted_color(World& w, CompData& cd, int remaining_hits)
{
	double transparency = cd.intersection.m_obj->m_material.m_transparency;

	double n_ratio = cd.n1 / cd.n2;
	double cos_i = dot(cd.eyev, cd.normalv);
	double sin2_t = std::pow(n_ratio, 2.0) * (1.0 - std::pow(cos_i, 2.0));

	if (transparency == 0.0 || remaining_hits == 0 || sin2_t > 1.0)
	{
		return BLACK;
	}

	double cos_t = std::sqrt(1.0 - sin2_t);
	Vector4 direction = cd.normalv * (n_ratio * cos_i - cos_t) - cd.eyev * n_ratio;

	Ray refract_ray{ PVpair(cd.under_pt, direction) };

	--remaining_hits;

	Color4 color{ color_at(w, refract_ray, remaining_hits) };

	return color * transparency;
}

double schlick(CompData& cd)
{
	double cos = dot(cd.eyev, cd.normalv);

	if (cd.n1 > cd.n2)
	{
		double n = cd.n1 / cd.n2;
		double sin2_t = n * n * (1.0 - cos * cos);
		if (sin2_t > 1.0) return 1.0;

		double cos_t = std::sqrt(1.0 - sin2_t);
		cos = cos_t;
	}

	double r0 = std::pow(((cd.n1 - cd.n2) / (cd.n1 + cd.n2)), 2.0);

	return r0 + (1.0 - r0) * std::pow((1.0 - cos), 5.0);
}

Color4 color_at(World& w, Ray& r, int remaining_hits)
{
	intersect(w, r);
	if (r.m_intersections.size() == 0) return Color4{ 0.0, 0.0, 0.0 };

	CompData cd = r.get_comp_data();

	if (cd.intersection.m_time > 1'000'000.0) 
	{
		return Color4(0.0, 0.0, 0.0);
	}

	return w.shade_hit(cd, remaining_hits);
}

World default_world()
{
	World w;

	Light l{ Point4(-10.0, 10.0, -10.0), Color4(1.0, 1.0, 1.0) };
	w.add_light(l);
	Sphere s1{ Material{ Color4(0.8, 1.0, 0.6) } };
	w.add_object(s1);
	w.m_shapes[0]->m_material.m_diffuse = 0.7;
	w.m_shapes[0]->m_material.m_specular = 0.2;
	Sphere s2{ scaling(0.5, 0.5, 0.5) };
	w.add_object(s2);

	return w;
}

bool is_shadowed(World& w, Point4& p, Light& l)
{
	Vector4 v = l.m_pos - p;
	double distance = magnitude(v);
	Vector4 dir = normalize(v);

	Ray r{ PVpair(p, dir) };
	intersect(w, r);
	if (r.m_intersections.size() == 0) return false;

	Intersection i{ r.hit() };
	if (i.m_time < distance && i.m_time > EPSILON)
	{
		return true;
	}
	return false;
}

void intersect(World& the_world, Ray& ray)
{
	for (auto sp : the_world.m_shapes)
	{
		ray.intersect(sp);
	}
}