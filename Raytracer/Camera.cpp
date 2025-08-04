#include "Camera.hpp"

Camera::Camera(int h, int v, float fov) : m_hsize{ h }, m_vsize{ v }, m_fov{ fov } 
{
	float half_view = std::tan(m_fov / 2.0f);
	float aspect_ratio = (float)m_hsize / (float)m_vsize;

	if (aspect_ratio >= 1.0f)
	{
		m_half_width = half_view;
		m_half_height = half_view / aspect_ratio;
	}
	else
	{
		m_half_width = half_view * aspect_ratio;
		m_half_height = half_view;
	}

	m_pixel_size = m_half_width * 2.0f / m_hsize;
}

ray Camera::ray_for_pixel(int px, int py)
{
	ray result;

	float xoffset = (px + 0.5f) * m_pixel_size;
	float yoffset = (py + 0.5f) * m_pixel_size;

	float world_x = m_half_width - xoffset;
	float world_y = m_half_height - yoffset;

	tuple pixel = m_transform.inverse() * point(world_x, world_y, -1);
	tuple origin = m_transform.inverse() * point(0, 0, 0);
	tuple direction = normalize(pixel - origin);

	result.m_origin = origin;
	result.m_direction = direction;

	return result;
}