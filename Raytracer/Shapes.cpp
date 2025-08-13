#include "Shapes.hpp"

//=== SPHERE ===
Vector4 Sphere::to_ray(Point4& ray_origin) const
{
	return ray_origin - m_position;
}

Vector4 Sphere::normal_at_local(const Point4& pt) const
{
	return pt - m_position;
}

std::vector<double> Sphere::intersect_ray(PVpair& ray)
{
	std::vector<double> times;

	Vector4 sph_to_ray = ray.origin - this->m_position;

	double a = dot(ray.direction, ray.direction);
	double b = 2 * dot(ray.direction, sph_to_ray);
	double c = dot(sph_to_ray, sph_to_ray) - 1.0;//1.0 is the radius of sphere( R * R )

	double delta = b * b - 4 * a * c;
	if (delta < 0) return times;

	times.emplace_back((-b - std::sqrt(delta)) / (2 * a));
	times.emplace_back((-b + std::sqrt(delta)) / (2 * a));

	return times;
}

//=== PLANE ===
Vector4 Plane::normal_at_local(const Point4& pt) const
{
	return Vector4{ 0.0, 1.0, 0.0 };
}

std::vector<double> Plane::intersect_ray(PVpair& ray)
{
	std::vector<double> times;

	if (std::abs(ray.direction.y) < EPSILON) return times;

	times.emplace_back(-ray.origin.y / ray.direction.y);

	return times;
}

Color4 pattern_at(Pattern& pat, Point4& loc)
{
	switch (pat.m_style)
	{
	case Styles::test_pattern:
		return Color4{ loc.x, loc.y, loc.z };

	case Styles::no_pattern:
		return pat.m_col1;

	case Styles::stripe:
		return (static_cast<int>(std::floor(loc.x)) % 2 == 0) ? pat.m_col1 : pat.m_col2;

	case Styles::gradient:
	{
		Color4 distance = pat.m_col2 - pat.m_col1;
		double fraction = loc.x - std::floor(loc.x);
		return pat.m_col1 + distance * fraction;
	}

	case Styles::ring:
	{
		int dist = static_cast<int>(std::floor(std::sqrt(loc.x * loc.x + loc.z * loc.z)));
		return (dist % 2 == 0) ? pat.m_col1 : pat.m_col2;
	}

	case Styles::checkerboard:
	{
		double sum = std::floor(loc.x + EPSILON) + std::floor(loc.y + EPSILON) + std::floor(loc.z + EPSILON);
		return (static_cast<int>(sum) % 2 == 0) ? pat.m_col1 : pat.m_col2;
	}

	default:
		return BLACK;
	}
}

Color4 pattern_at_shape(mat4x4& shape_transf, Material& mat, Point4& loc)
{
	Point4 sph_loc = shape_transf.inverse() * loc;
	Point4 pat_loc = mat.m_pattern.m_transform.inverse() * sph_loc;

	return pattern_at(mat.m_pattern, pat_loc);
}

Sphere glass_sphere()
{
	Sphere res;
	res.m_material.m_transparency = 1.0;
	res.m_material.m_refractive = 1.5;

	return res;
}