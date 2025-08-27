#ifndef _SPHERE_
#define _SPHERE_

#include <vector>
#include <memory>
#include <algorithm>
#include <initializer_list>

#include "Tuples.hpp"
#include "Matrix.hpp"
#include "Material.hpp"
#include "PVpair.hpp"

class Group;

class Shape {
public:
	Group* m_parent = nullptr;
	//Point4 m_position{ 0.0, 0.0, 0.0 };
	mat4x4 m_transform = i4x4;
	Material m_material;

	Shape() = default;
	Shape(mat4x4 tr) : m_transform{ tr } {}
	Shape(Material mat) : m_material{ mat } {}
	Shape(Material mat, mat4x4 tr) : m_material{ mat }, m_transform{ tr } {}
	~Shape() = default;

	virtual std::vector<std::pair<double, Shape*>> intersect_ray(PVpair) = 0;
	virtual Vector4 normal_at_local(const Point4&) const = 0;
};

class TestShape : public Shape {
public:
	using Shape::Shape;

	std::vector<std::pair<double, Shape*>> intersect_ray(PVpair) { return std::vector<std::pair<double, Shape*>>{}; };
	Vector4 normal_at_local(const Point4&) const { return Vector4(); }
};

class Sphere : public Shape{
public:
	using Shape::Shape;

	std::vector<std::pair<double, Shape*>> intersect_ray(PVpair);
	Vector4 to_ray(Point4&) const;
	Vector4 normal_at_local(const Point4&) const;
};

class Plane : public Shape {
public:
	using Shape::Shape;

	std::vector<std::pair<double, Shape*>> intersect_ray(PVpair);
	Vector4 normal_at_local(const Point4&) const;
};

class Cube : public Shape {
public:
	using Shape::Shape;

	std::vector<std::pair<double, Shape*>> intersect_ray(PVpair);
	Vector4 normal_at_local(const Point4&) const;
	std::pair<double, double> check_axis(double, double);
};

class Cylinder : public Shape {
public:
	using Shape::Shape;
	float m_minimum = -INFINITY;
	float m_maximum = INFINITY;
	bool m_closed = false;

	std::vector<std::pair<double, Shape*>> intersect_ray(PVpair);
	Vector4 normal_at_local(const Point4&) const;
	std::pair<double, double> check_axis(double, double);
	void intersect_caps(PVpair& ray, std::vector<std::pair<double, Shape*>>& times);
};
bool check_caps(PVpair& ray, double t, double radius = 1.0);

class Cone : public Shape {
public:
	using Shape::Shape;
	float m_minimum = -INFINITY;
	float m_maximum = INFINITY;
	bool m_closed = false;

	std::vector<std::pair<double, Shape*>> intersect_ray(PVpair);
	Vector4 normal_at_local(const Point4&) const;
	std::pair<double, double> check_axis(double, double);
	void intersect_caps(PVpair& ray, std::vector<std::pair<double, Shape*>>& times);
};

class Group : public Shape {
public:
	static std::vector<Shape*> track_nodes;
	static void delete_track_nodes()
	{
		for (auto p : Group::track_nodes)
		{
			delete p;
		}
		Group::track_nodes.clear();
	}

	using Shape::Shape;

	std::vector<Shape*> m_children;

	std::vector<std::pair<double, Shape*>> intersect_ray(PVpair);
	Vector4 normal_at_local(const Point4&) const;
	std::pair<double, double> check_axis(double, double);

	template<std::derived_from<Shape> T>
	inline void add_child(T* child);
	template<std::derived_from<Shape> T>
	inline void add_child(T& child);
};

template<std::derived_from<Shape> T>
inline void Group::add_child(T* child)
{
	child->m_parent = this;
	m_children.emplace_back(child);
	Group::track_nodes.emplace_back(child);
}

template<std::derived_from<Shape> T>
inline void Group::add_child(T& child)
{
	T* node = new T(child);
	node->m_parent = this;
	m_children.emplace_back(node);
	Group::track_nodes.emplace_back(node);
}

class Triangle : public Shape {
public:
	using Shape::Shape;

	Point4 m_pt1{ 0.0, 0.0, 0.0 };
	Point4 m_pt2{ 0.0, 0.0, 0.0 };
	Point4 m_pt3{ 0.0, 0.0, 0.0 };
	Vector4 m_e1{ 0.0, 0.0, 0.0 };
	Vector4 m_e2{ 0.0, 0.0, 0.0 };
	Vector4 m_normal{ 0.0, 0.0, 0.0 };


	Triangle(Point4, Point4, Point4);
	Triangle(Point4, Point4, Point4, Material);

	std::vector<std::pair<double, Shape*>> intersect_ray(PVpair);
	Vector4 normal_at_local(const Point4&) const;
};

Color4 pattern_at(Pattern&, Point4&);
Color4 pattern_at_shape(mat4x4& sh_inv, Material& mat, Point4& loc);

Sphere glass_sphere();

#endif
