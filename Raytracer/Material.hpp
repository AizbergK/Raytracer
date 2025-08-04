#ifndef _MATERIAL_
#define _MATERIAL_

#include "Tuples.hpp"

class material {
public:
	tuple m_albedo = color(1, 1, 1);
	float m_ambient = 0.1f;
	float m_diffuse = 0.9f;
	float m_specular = 0.9f;
	float m_shininess = 200.0f;
};

#endif