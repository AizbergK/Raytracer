#include "PointLight.hpp"

pt_lght::pt_lght(tuple pt, tuple color) : m_pos{ pt }, m_intensity{ color } {}

tuple lighting(material& mat, pt_lght& pl, tuple& pos, tuple& eyev, tuple& normalv)
{
	tuple effective_color = hadamard(mat.m_albedo, pl.m_intensity);
	tuple lightv = normalize(pl.m_pos - pos);
	tuple ambient = effective_color * mat.m_ambient;
	float light_dot_normal = dot(lightv, normalv);

	tuple diffuse;
	tuple specular;
	tuple reflectv;
	float reflect_dot_eye = 0.0f;
	if (light_dot_normal < 0.0f)
	{
		diffuse = color(0, 0, 0);
		specular = color(0, 0, 0);
	}
	else
	{
		diffuse = effective_color * mat.m_diffuse * light_dot_normal;
		reflectv = reflect(-lightv, normalv);
		reflect_dot_eye = dot(reflectv, eyev);
	}

	if (reflect_dot_eye <= 0.0f)
	{
		specular = color(0, 0, 0);
	}
	else
	{
		float factor = std::pow(reflect_dot_eye, mat.m_shininess);
		specular = pl.m_intensity * mat.m_specular * factor;
	}

	return ambient + diffuse + specular;
}
