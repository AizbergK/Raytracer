#ifndef _CAMERA_
#define _CAMERA_

#include "Matrix.hpp"
#include "Ray.hpp"

class Camera {
public:
	int m_hsize = 0;
	int m_vsize = 0;
	float m_fov = 0.0f;
	float m_pixel_size = 0.0f;
	float m_half_width = 0.0f;
	float m_half_height = 0.0f;
	mat4x4 m_transform = i4x4;

	Camera() = default;
	Camera(int, int, float);
	~Camera() = default;

	ray ray_for_pixel(int, int);
};

#endif
