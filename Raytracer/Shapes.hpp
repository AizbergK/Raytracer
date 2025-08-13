#ifndef _SPHERE_
#define _SPHERE_

#include <vector>
#include <memory>

#include "Tuples.hpp"
#include "Matrix.hpp"
#include "Material.hpp"
#include "PVpair.hpp"

class Shape {
public:
	Point4 m_position{ 0.0, 0.0, 0.0 };
	mat4x4 m_transform = i4x4;
	Material m_material;

	Shape() = default;
	Shape(mat4x4 tr) : m_transform{ tr } {}
	Shape(Material mat) : m_material{ mat } {}
	Shape(Material mat, mat4x4 tr) : m_material{ mat }, m_transform{ tr } {}
	~Shape() = default;

	virtual std::shared_ptr<Shape> get_ptr() = 0;
	virtual std::vector<double> intersect_ray(PVpair&) = 0;
	virtual Vector4 normal_at_local(const Point4&) const = 0;
};

class TestShape : public Shape {
public:
	using Shape::Shape;

	std::shared_ptr<Shape> get_ptr() { return std::make_shared<TestShape>(*this); }
	std::vector<double> intersect_ray(PVpair&) { return std::vector<double>{}; };
	Vector4 normal_at_local(const Point4&) const { return Vector4(); }
};

class Sphere : public Shape{
public:
	using Shape::Shape;

	std::shared_ptr<Shape> get_ptr() { return std::make_shared<Sphere>(*this); }
	std::vector<double> intersect_ray(PVpair&);
	Vector4 to_ray(Point4&) const;
	Vector4 normal_at_local(const Point4&) const;
};

class Plane : public Shape {
public:
	using Shape::Shape;

	std::shared_ptr<Shape> get_ptr() { return std::make_shared<Plane>(*this); }
	std::vector<double> intersect_ray(PVpair&);
	Vector4 normal_at_local(const Point4&) const;
};

Color4 pattern_at(Pattern&, Point4&);
Color4 pattern_at_shape(mat4x4& sh_inv, Material& mat, Point4& loc);

Sphere glass_sphere();

#endif
