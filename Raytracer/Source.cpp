#include <iostream>

#include "Helpers.hpp"
#include "Tuples.hpp"
#include "ImgBuf.hpp"
#include "Matrix.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "Intersection.hpp"
#include "PointLight.hpp"
#include "World.hpp"
#include "Camera.hpp"

world create_world();
Camera create_camera();

int main()
{
	world w{ create_world() };
	Camera c{ create_camera() };
	render(c, w).writeBMP("C:\\Users\\atzbe\\Desktop\\bmps");
	
	return 0;
}

Camera create_camera()
{
	Camera c{ 1920, 1080, PI / 3.0f };
	c.m_transform = view_transform(point(0.0f, 1.5f, -5.0f), point(0.0f, 1.0f, 0.0f), vector(0.0f, 1.0f, 0.0f));

	return c;
}

world create_world()
{
	world w;
	
	sphere floor{ material{ color(1.0f, 0.9f, 0.9f) }, scaling(10.0f, 0.01f, 10.0f) };
	floor.m_material.m_specular = 0;
	sphere left_wall{ translation(0.0f, 0.0f, 5.0f) * rotation(PI / 2.0f, -PI / 4.0f, 0.0f) * scaling(10.0f, 0.01f, 10.0f) };
	left_wall.m_material = floor.m_material;
	sphere right_wall{ translation(0.0f, 0.0f, 5.0f) * rotation(PI / 2.0f, PI / 4.0f, 0.0f) * scaling(10.0f, 0.01f, 10.0f) };
	right_wall.m_material = floor.m_material;

	w.add_object(floor);
	w.add_object(left_wall);
	w.add_object(right_wall);

	sphere middle{ material{ color(0.1f, 1.0f, 0.5f) }, translation(-0.5f, 1.0f, 0.5f) };
	middle.m_material.m_diffuse = 0.7f;
	middle.m_material.m_specular = 0.3f;

	sphere right{ material{ color(0.5f, 1.0f, 0.1f) }, translation(1.5f, 0.5f, -0.5f) * scaling(0.5f, 0.5f, 0.5f) };
	right.m_material.m_diffuse = 0.7f;
	right.m_material.m_specular = 0.3f;

	sphere left{ material{ color(1.0f, 0.8f, -0.75f) }, translation(-1.5f, 0.33f, -0.75f) * scaling(0.33f, 0.33f, 0.33f) };
	left.m_material.m_diffuse = 0.7f;
	left.m_material.m_specular = 0.3f;

	w.add_object(middle);
	w.add_object(right);
	w.add_object(left);

	pt_lght top_left{ point(-10.0f, 10.0f, -10.0f), color(1.0f, 1.0f, 1.0f) };
	w.add_light(top_left);

	return w;
}