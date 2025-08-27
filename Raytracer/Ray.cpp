#include "Ray.hpp"

Ray::Ray(PVpair pv) : m_origin_dir{ pv } {}

Point4 Ray::position(double time) 
{
	return m_origin_dir.origin + time * m_origin_dir.direction;
}

void Ray::intersect(Shape* shape)
{
	auto times = shape->intersect_ray(this->get_pv());
	for (auto& p : times)
	{
		Intersection i{ p };
		m_intersections.emplace_back(i);
	}
}

PVpair Ray::get_pv()
{
	return PVpair(this->m_origin_dir.origin, this->m_origin_dir.direction);
}

Intersection Ray::hit()
{
	Intersection the_hit;
	the_hit.m_time = INFINITY;

	for (auto& i : m_intersections)
		if (i.m_time >= 0.0 && the_hit.m_time > i.m_time)
			the_hit = i;

	return the_hit;
}

void Ray::add_intersection(Intersection& inter)
{
	m_intersections.emplace_back(inter);
}

CompData Ray::get_comp_data(std::optional<int> opt)
{
	CompData result;

	result.intersection = this->hit();
	if (result.intersection.m_time > 1'000'000.0) 
	{
		return result;
	}
	result.pt = this->position(result.intersection.m_time);
	result.eyev = -this->m_origin_dir.direction;


	result.normalv = normal_at(result);
	
	if (dot(result.eyev, result.normalv) < 0.0)
	{
		result.is_inside = true;
		result.normalv = -result.normalv;
	}
	result.over_pt = result.pt + result.normalv * EPSILON;
	result.under_pt = result.pt - result.normalv * EPSILON;

	result.reflectv = reflect(m_origin_dir.direction, result.normalv);

	auto intersections = this->m_intersections;
	std::sort(intersections.begin(), intersections.end(), [](Intersection& a, Intersection& b) {
		return a.m_time < b.m_time;
	});

	std::vector<Shape*> containers;

	Intersection test_intersection = result.intersection;
	if(opt.has_value())
	{
		test_intersection = intersections[opt.value()];
	}

	for (auto inter : intersections)
	{
		if (inter == test_intersection)
		{
			if (containers.size() == 0)
			{
				result.n1 = 1.0;
			}
			else
			{
				result.n1 = (*containers.rbegin())->m_material.m_refractive;
			}
		}
		auto it = std::find(containers.begin(), containers.end(), inter.m_obj);

		if (it == containers.end())
		{
			containers.emplace_back(inter.m_obj);
		}
		else
		{
			containers.erase(it);
		}

		if (inter == test_intersection)
		{
			if (containers.size() == 0)
			{
				result.n2 = 1.0;
			}
			else
			{
				result.n2 = (*containers.rbegin())->m_material.m_refractive;
			}
		}
	}
	

	return result;
}

Vector4 Ray::normal_at(CompData cd)
{
	mat4x4 transf{ cd.intersection.m_obj->m_transform };
	for (Group* p = cd.intersection.m_obj->m_parent; p; p = p->m_parent)
	{
		transf = p->m_transform * transf;
	}

	auto world_center = transf * Point4(0, 0, 0);

	mat4x4 world_to_local = transf.inverse();

	Vector4 local_normal = cd.intersection.m_obj->normal_at_local(world_to_local * cd.pt);
	Vector4 world_normal = world_to_local.transpose() * local_normal;

	return normalize(world_normal);
}