#ifndef _MATERIAL_
#define _MATERIAL_

#include "Tuples.hpp"
#include "Patterns.hpp"

class Material {
public:
	double m_ambient = 0.1;
	double m_diffuse = 0.9;
	double m_specular = 0.9;
	double m_shininess = 200.0;
	double m_reflective = 0.0;
	double m_transparency = 0.0;
	double m_refractive = 1.0;
	Pattern m_pattern;

	Material() = default;
	Material(Color4);
	Material(Pattern);
};

#endif