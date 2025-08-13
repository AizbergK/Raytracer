#include "Camera.hpp"

Camera::Camera(int h, int v, double fov) : m_hsize{ h }, m_vsize{ v }, m_fov{ fov } 
{
	double half_view = std::tan(m_fov / 2.0);
	double aspect_ratio = (double)m_hsize / (double)m_vsize;

	if (aspect_ratio >= 1.0)
	{
		m_half_width = half_view;
		m_half_height = half_view / aspect_ratio;
	}
	else
	{
		m_half_width = half_view * aspect_ratio;
		m_half_height = half_view;
	}

	m_pixel_size = m_half_width * 2.0 / m_hsize;
}

Ray Camera::ray_for_pixel(int px, int py)
{
	Ray result;

	double xoffset = (px + 0.5) * m_pixel_size;
	double yoffset = (py + 0.5) * m_pixel_size;

	double world_x = m_half_width - xoffset;
	double world_y = m_half_height - yoffset;

	Point4 pixel = m_transform.inverse() * Point4(world_x, world_y, -1.0);
	Point4 origin = m_transform.inverse() * Point4(0.0, 0.0, 0.0);
	Vector4 direction = normalize(pixel - origin);

	result.m_origin_dir.origin = origin;
	result.m_origin_dir.direction = direction;

	return result;
}