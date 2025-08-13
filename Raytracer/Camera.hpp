#ifndef _CAMERA_
#define _CAMERA_

#include "Matrix.hpp"
#include "Ray.hpp"

class Camera {
public:
	int m_hsize = 0;
	int m_vsize = 0;
	double m_fov = 0.0;
	double m_pixel_size = 0.0;
	double m_half_width = 0.0;
	double m_half_height = 0.0;
	mat4x4 m_transform = i4x4;

	Camera() = default;
	Camera(int, int, double);
	~Camera() = default;

	Ray ray_for_pixel(int, int);
};

#endif
