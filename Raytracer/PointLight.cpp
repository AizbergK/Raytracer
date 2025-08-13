#include "PointLight.hpp"

Light::Light(Point4 pt, Color4 col) : m_pos{ pt }, m_intensity{ col } {}

Color4 lighting(Intersection& inter, Light& pl, Point4& pos, Vector4& eyev, Vector4& normalv, bool in_shadow)
{
	Material& mat = inter.m_obj->m_material;
	Color4 point_color{ pattern_at_shape(inter.m_obj->m_transform, mat, pos)};
	Color4 effective_color = hadamard(point_color, pl.m_intensity);
	Vector4 lightv = normalize(pl.m_pos - pos);
	Color4 ambient = effective_color * mat.m_ambient;
	double light_dot_normal = dot(lightv, normalv);

	Color4 diffuse;
	Color4 specular;
	Vector4 reflectv;
	double reflect_dot_eye = 0.0;

	if (light_dot_normal < 0.0 || in_shadow)
	{
		diffuse = Color4(0, 0, 0);
		specular = Color4(0, 0, 0);
	}
	else
	{
		diffuse = effective_color * mat.m_diffuse * light_dot_normal;
		reflectv = reflect(-lightv, normalv);
		reflect_dot_eye = dot(reflectv, eyev);
	}

	if (reflect_dot_eye <= 0.0)
	{
		specular = Color4(0, 0, 0);
	}
	else
	{
		double factor = std::pow(reflect_dot_eye, mat.m_shininess);
		specular = pl.m_intensity * mat.m_specular * factor;
	}

	return ambient + diffuse + specular;
}