#ifndef _POINTLIGHT_
#define _POINTLIGHT_

#include "Tuples.hpp"
#include "Material.hpp"
#include "Shapes.hpp"
#include "Intersection.hpp"

class Light {
public:
	Point4 m_pos{ 0.0, 0.0, 0.0 };
	Color4 m_intensity{ 0.0, 0.0, 0.0 };

	Light() = default;
	Light(Point4 pos, Color4 col);
	~Light() = default;
};

Color4 lighting(Intersection&, Light&, Point4& pos, Vector4& ray_dir, Vector4& norm, bool in_shadow = false);

#endif