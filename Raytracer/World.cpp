#include "World.hpp"


void world::add_light(pt_lght lgth)
{
	m_point_lights.emplace_back(lgth);
}


void world::add_object(sphere sph)
{
	m_spheres.emplace_back(sph);
}

tuple world::shade_hit(comp_data comps)
{
	tuple result_color{ color(0.0f, 0.0f, 0.0f) };
	for(auto& pl : m_point_lights)
		result_color = result_color + lighting(comps.inter.m_obj->m_material, pl, comps.pt, comps.eyev, comps.normalv);

	return result_color;// / this->m_point_lights.size();
}

tuple color_at(world& w, ray& r)
{
	r.intersect(w);
	if (r.m_intersections.size() == 0) return color(0.0f, 0.0f, 0.0f);

	comp_data cd = r.get_comp_data();

	return w.shade_hit(cd);
}

world default_world()
{
	world w;

	w.add_light(pt_lght{ point(-10.0f, 10.0f, -10.0f), color(1.0f, 1.0f, 1.0f) });
	w.add_object(sphere{ material{ color(0.8f, 1.0f, 0.6f) } });
	w.m_spheres[0].m_material.m_diffuse = 0.7f;
	w.m_spheres[0].m_material.m_specular = 0.2f;
	w.add_object(sphere{ scaling(0.5f, 0.5f, 0.5f) });

	return w;
}