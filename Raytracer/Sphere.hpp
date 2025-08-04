#ifndef _SPHERE_
#define _SPHERE_

#include "Tuples.hpp"
#include "Matrix.hpp"
#include "Material.hpp"

class sphere {
public:
	tuple m_position = point(0, 0, 0);
	float m_radius = 1.0f;
	mat4x4 m_transform = i4x4;
	material m_material;

	sphere() = default;
	sphere(mat4x4 tr) : m_transform{ tr } {}
	sphere(material mat) : m_material{ mat } {}
	sphere(material mat, mat4x4 tr) : m_material{ mat }, m_transform { tr } {}
	~sphere() = default;

	tuple to_ray(tuple&) const;
	tuple normal_at(tuple) const;
};

#endif
