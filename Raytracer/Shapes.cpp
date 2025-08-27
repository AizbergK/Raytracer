#include "Shapes.hpp"

//=== SPHERE ===
Vector4 Sphere::to_ray(Point4& ray_origin) const
{
	return ray_origin - Point4(0.0, 0.0, 0.0);//m_position;
}

Vector4 Sphere::normal_at_local(const Point4& pt) const
{
	return pt - Point4(0.0, 0.0, 0.0);//m_position;
}

std::vector<std::pair<double, Shape*>> Sphere::intersect_ray(PVpair ray)
{
	mat4x4 inv = this->m_transform.inverse();
	ray.direction = inv * ray.direction;
	ray.origin = inv * ray.origin;

	std::vector<std::pair<double, Shape*>> times;

	Vector4 sph_to_ray = ray.origin - Point4(0.0, 0.0, 0.0);//this->m_position;

	double a = dot(ray.direction, ray.direction);
	double b = 2 * dot(ray.direction, sph_to_ray);
	double c = dot(sph_to_ray, sph_to_ray) - 1.0;//1.0 is the radius of sphere( R * R )

	double delta = b * b - 4 * a * c;
	if (delta < 0) return times;

	times.emplace_back( (-b - std::sqrt(delta)) / (2 * a), this );
	times.emplace_back( (-b + std::sqrt(delta)) / (2 * a), this );

	return times;
}

//=== PLANE ===
Vector4 Plane::normal_at_local(const Point4& pt) const
{
	return Vector4{ 0.0, 1.0, 0.0 };
}

std::vector<std::pair<double, Shape*>> Plane::intersect_ray(PVpair ray)
{
	mat4x4 inv = this->m_transform.inverse();
	ray.direction = inv * ray.direction;
	ray.origin = inv * ray.origin;

	std::vector<std::pair<double, Shape*>> times;

	if (std::abs(ray.direction.y) < EPSILON) return times;

	times.emplace_back( -ray.origin.y / ray.direction.y, this );

	return times;
}

//=== CUBE ===
Vector4 Cube::normal_at_local(const Point4& pt) const
{
	double max_val = std::max({ std::abs(pt.x), std::abs(pt.y), std::abs(pt.z) });

	if (max_val == std::abs(pt.x))
		return Vector4{ pt.x, 0.0, 0.0 };
	if (max_val == std::abs(pt.y))
		return Vector4{ 0.0, pt.y, 0.0 };

	return Vector4{ 0.0, 0.0, pt.z };
}

std::pair<double, double> Cube::check_axis(double origin, double direction)
{
	double tmin, tmax;
	double tmin_numerator = -1 - origin;
	double tmax_numerator = 1 - origin;

	if (std::abs(direction) >= EPSILON)
	{
		tmin = tmin_numerator / direction;
		tmax = tmax_numerator / direction;
	}
	else
	{
		tmin = tmin_numerator * INFINITY;
		tmax = tmax_numerator * INFINITY;
	}

	if (tmin > tmax) std::swap(tmin, tmax);

	return { tmin, tmax };
}

std::vector<std::pair<double, Shape*>> Cube::intersect_ray(PVpair ray)
{
	mat4x4 inv = this->m_transform.inverse();
	ray.direction = inv * ray.direction;
	ray.origin = inv * ray.origin;

	std::vector<std::pair<double, Shape*>> times;

	auto [xtmin, xtmax] = check_axis(ray.origin.x, ray.direction.x);
	auto [ytmin, ytmax] = check_axis(ray.origin.y, ray.direction.y);
	auto [ztmin, ztmax] = check_axis(ray.origin.z, ray.direction.z);

	double tmin = std::max({ xtmin, ytmin, ztmin });
	double tmax = std::min({ xtmax, ytmax, ztmax });

	if (tmin > tmax) return times;

	times.emplace_back( tmin, this );
	times.emplace_back( tmax, this );

	return times;
}

//=== CYLINDER ===
Vector4 Cylinder::normal_at_local(const Point4& pt) const
{
	double dist = pt.x * pt.x + pt.z * pt.z;

	if (dist < 1.0 && pt.y >= this->m_maximum - EPSILON)
		return Vector4(0.0, 1.0, 0.0);
	if (dist < 1.0 && pt.y <= this->m_minimum + EPSILON)
		return Vector4(0.0, -1.0, 0.0);

	return Vector4(pt.x, 0.0, pt.z);
}

bool check_caps(PVpair& ray, double t, double radius)
{
	double x = ray.origin.x + t * ray.direction.x;
	double z = ray.origin.z + t * ray.direction.z;

	return (x * x + z * z) <= radius;
}

void Cylinder::intersect_caps(PVpair& ray, std::vector<std::pair<double, Shape*>>& times)
{
	if (this->m_closed == false) return;

	double t0 = (this->m_minimum - ray.origin.y) / ray.direction.y;
	if (check_caps(ray, t0))
	{
		times.emplace_back( t0, this );
	}

	double t1 = (this->m_maximum - ray.origin.y) / ray.direction.y;
	if (check_caps(ray, t1))
	{
		times.emplace_back( t1, this );
	}
}

std::vector<std::pair<double, Shape*>> Cylinder::intersect_ray(PVpair ray)
{
	mat4x4 inv = this->m_transform.inverse();
	ray.direction = inv * ray.direction;
	ray.origin = inv * ray.origin;

	std::vector<std::pair<double, Shape*>> times;

	double a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
	if (a < EPSILON && this->m_closed == false) return times;

	double b = ray.origin.x * ray.direction.x * 2.0 + ray.origin.z * ray.direction.z * 2.0;
	double c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - 1.0;

	double disc = b * b - 4.0 * a * c;

	if (disc < 0.0) return times;

	double t0 = (-b - std::sqrt(disc)) / (2.0 * a);
	double t1 = (-b + std::sqrt(disc)) / (2.0 * a);
	
	intersect_caps(ray, times);

	double y0 = ray.origin.y + t0 * ray.direction.y;
	if(this->m_minimum < y0 && y0 < this->m_maximum)
	{
		times.emplace_back( t0, this );
	}

	double y1 = ray.origin.y + t1 * ray.direction.y;
	if (this->m_minimum < y1 && y1 < this->m_maximum)
	{
		times.emplace_back( t1, this );
	}

	return times;
}

//=== CONE ===
Vector4 Cone::normal_at_local(const Point4& pt) const
{
	double dist = pt.x * pt.x + pt.z * pt.z;
	if (dist < 1.0 && pt.y >= this->m_maximum - EPSILON)
		return Vector4(0.0, 1.0, 0.0);
	if (dist < 1.0 && pt.y <= this->m_minimum + EPSILON)
		return Vector4(0.0, -1.0, 0.0);

	double y = std::sqrt(pt.x * pt.x + pt.z * pt.z);
	return Vector4(pt.x, pt.y > 0 ? -y : y, pt.z);
}

void Cone::intersect_caps(PVpair& ray, std::vector<std::pair<double, Shape*>>& times)
{
	if (this->m_closed == false) return;

	double t0 = (this->m_minimum - ray.origin.y) / ray.direction.y;
	if (check_caps(ray, t0, std::abs(this->m_minimum)))
	{
		times.emplace_back( t0, this );
	}

	double t1 = (this->m_maximum - ray.origin.y) / ray.direction.y;
	if (check_caps(ray, t1, std::abs(this->m_maximum)))
	{
		times.emplace_back( t1, this );
	}
}

std::vector<std::pair<double, Shape*>> Cone::intersect_ray(PVpair ray)
{
	mat4x4 inv = this->m_transform.inverse();
	ray.direction = inv * ray.direction;
	ray.origin = inv * ray.origin;

	std::vector<std::pair<double, Shape*>> times;

	double a =	ray.direction.x * ray.direction.x -
				ray.direction.y * ray.direction.y +
				ray.direction.z * ray.direction.z;

	double b =	ray.origin.x * ray.direction.x * 2.0 -
				ray.origin.y * ray.direction.y * 2.0 +
				ray.origin.z * ray.direction.z * 2.0;

	if (std::abs(a) < EPSILON && std::abs(b) < EPSILON) return times;

	double c =	ray.origin.x * ray.origin.x -
				ray.origin.y * ray.origin.y +
				ray.origin.z * ray.origin.z;

	if (std::abs(a) < EPSILON)
	{
		times.emplace_back( -c / (2.0 * b), this );
	}

	double disc = b * b - 4.0 * a * c;

	if (disc < 0.0) return times;

	double t0 = (-b - std::sqrt(disc)) / (2.0 * a);
	double t1 = (-b + std::sqrt(disc)) / (2.0 * a);

	intersect_caps(ray, times);

	double y0 = ray.origin.y + t0 * ray.direction.y;
	if (this->m_minimum < y0 && y0 < this->m_maximum)
	{
		times.emplace_back( t0, this );
	}

	double y1 = ray.origin.y + t1 * ray.direction.y;
	if (this->m_minimum < y1 && y1 < this->m_maximum)
	{
		times.emplace_back( t1, this );
	}

	return times;
}

//=== GROUP ===
std::vector<Shape*> Group::track_nodes{}; 

std::vector<std::pair<double, Shape*>> Group::intersect_ray(PVpair ray)
{
	mat4x4 inv = this->m_transform.inverse();
	ray.direction = inv * ray.direction;
	ray.origin = inv * ray.origin;

	std::vector<std::pair<double, Shape*>> times;

	for (Shape* child : this->m_children)
	{
		std::vector<std::pair<double, Shape*>> results = child->intersect_ray(ray);
		times.insert(times.end(), results.begin(), results.end());
	}

	return times;
}

Vector4 Group::normal_at_local(const Point4& pt) const
{
	throw;
}

//=== TRIANGLE ===
Triangle::Triangle(Point4 p1, Point4 p2, Point4 p3) : m_pt1{ p1 }, m_pt2{ p2 }, m_pt3{ p3 }, m_e1{ p2 - p1 }, m_e2{ p3 - p1 } 
{
	m_normal = normalize(cross(m_e2, m_e1));
}
Triangle::Triangle(Point4 p1, Point4 p2, Point4 p3, Material mat) : m_pt1{ p1 }, m_pt2{ p2 }, m_pt3{ p3 }, m_e1{ p2 - p1 }, m_e2{ p3 - p1 }, Shape(mat)
{
	m_normal = normalize(cross(m_e2, m_e1));
}

Vector4 Triangle::normal_at_local(const Point4& pt) const
{
	return this->m_normal;
}

std::vector<std::pair<double, Shape*>> Triangle::intersect_ray(PVpair ray)
{
	mat4x4 inv = this->m_transform.inverse();
	ray.direction = inv * ray.direction;
	ray.origin = inv * ray.origin;

	std::vector<std::pair<double, Shape*>> times;

	auto dir_cross_e2 = cross(ray.direction, this->m_e2);
	auto det = dot(this->m_e1, dir_cross_e2);

	if (std::abs(det) < EPSILON) return times;

	auto f = 1.0 / det;

	auto p1_to_origin = ray.origin - this->m_pt1;
	auto u = f * dot(p1_to_origin, dir_cross_e2);
	if (u < 0 || u > 1) return times;

	auto origin_cross_e1 = cross(p1_to_origin, this->m_e1);
	auto v = f * dot(ray.direction, origin_cross_e1);
	if (v < 0 || (u + v) > 1) return times;

	auto t = f * dot(this->m_e2, origin_cross_e1);
	times.emplace_back(t, this);

	return times;
}

//=== OTHER ===
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