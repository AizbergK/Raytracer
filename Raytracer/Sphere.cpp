#include "Sphere.hpp"

tuple sphere::to_ray(tuple& ray_origin) const
{
	return ray_origin - m_position;
}

tuple sphere::normal_at(tuple pt) const
{
	auto inv = m_transform.inverse();
	pt = inv * pt;
	tuple nm = pt - m_position;
	nm = inv.transpose() * nm;
	nm.w = 0.0f;
	return normalize(nm);
}