#include "Helpers.hpp"
#include "Tuples.hpp"
#include "Matrix.hpp"
#include "ImgBuf.hpp"
#include "Shapes.hpp"
#include "PointLight.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Patterns.hpp"

class Scene {
public:
	World world;
	Camera camera;
};

Scene create_test_scene(int);

Scene create_refraction_ball_scene(int);
Scene create_reflection_scene(int);

int main()
{
	//Scene scene{ create_test_scene(200) };

	//Scene scene{ create_refraction_ball_scene(2000) };
	Scene scene{ create_reflection_scene(2000) };

	render(scene.camera, scene.world, 5).writeBMP("C:\\Users\\atzbe\\Desktop\\bmps");
	
	return 0;
}

Scene create_test_scene(int size)
{
	Scene s;

	Camera c{ size, size, DEG_30 };
	c.m_transform = view_transform(Point4(0.0, 1.5, -5.0), Point4(0.0, 0.0, 0.0), Vector4(0.0, 1.0, 0.0));
	s.camera = c;

	World w;

	//Walls
	Plane floor{ Material{ checkers_pattern(WHITE, BLACK) } };
	floor.m_material.m_specular = 0;
	w.add_object(floor);

	//Lights
	double tl_lght_int = 1.0;
	Light top_left{ Point4(-10.0, 10.0, -10.0), Color4(tl_lght_int, tl_lght_int, tl_lght_int) };
	w.add_light(top_left);
	s.world = w;

	return s;
}

Scene create_refraction_ball_scene(int size)
{
	Scene s;

	Camera c{ size, size, DEG_30 };
	c.m_transform = view_transform(Point4(0.0, 0.0, -5.0), Point4(0.0, 0.0, 0.0), Vector4(0.0, 1.0, 0.0));
	s.camera = c;

	World w;
	
	//Walls
	Plane floor{ Material{ checkers_pattern(WHITE, WHITE * 0.1) }, translation(0.0, 0.0, 9.9) * rotation(DEG_90, 0.0, 0.0) };
	floor.m_material.m_specular = 0;
	w.add_object(floor);

	// --- Glass Sphere (outer) ---
	Sphere glass_sphere;
	glass_sphere.m_material.m_pattern = no_pat(Color4(1, 1, 1));
	glass_sphere.m_material.m_ambient = 0.0;
	glass_sphere.m_material.m_diffuse = 0.1;
	glass_sphere.m_material.m_specular = 0.9;
	glass_sphere.m_material.m_shininess = 300.0;
	glass_sphere.m_material.m_reflective = 0.9;
	glass_sphere.m_material.m_transparency = 0.9;
	glass_sphere.m_material.m_refractive = 1.5;

	// --- Air Bubble (inner) ---
	Sphere air_bubble;
	air_bubble.m_transform = scaling(0.5, 0.5, 0.5);
	air_bubble.m_material.m_pattern = no_pat(Color4(1, 1, 1));
	air_bubble.m_material.m_ambient = 0.0;
	air_bubble.m_material.m_diffuse = 0.0;
	air_bubble.m_material.m_specular = 0.9;
	air_bubble.m_material.m_shininess = 300.0;
	air_bubble.m_material.m_reflective = 1.0;
	air_bubble.m_material.m_transparency = 1.0;
	air_bubble.m_material.m_refractive = 1.0;

	// --- Add to world ---
	w.add_object(glass_sphere);
	w.add_object(air_bubble);

	//Lights
	double tl_lght_int = 1.0;
	Light top_left{ Point4(-3.0, 10.0, -3.0), Color4(tl_lght_int, tl_lght_int, tl_lght_int) };
	w.add_light(top_left);
	s.world = w;
	return s;
}

Scene create_reflection_scene(int size)
{
	Scene s;

	Camera c{ size, size / 2, DEG_60 };
	c.m_transform = view_transform(Point4(0.0, 1.5, -5.5), Point4(0.0, 1.0, 0.0), Vector4(0.0, 1.0, 0.0));
	s.camera = c;

	World w;

	// === LIGHT ===
	Light l{ Point4(-10.0, 10.0, -10.0), WHITE };
	w.add_light(l);

	// === WALLS  ===
	Plane floor;
	floor.m_material.m_pattern = checkers_pattern(WHITE, BLACK); // checkers_pattern(Color4(1, 1, 1), Color4(0, 0, 0));
	floor.m_material.m_specular = 0.0;
	floor.m_material.m_reflective = 0.1;
	w.add_object(floor);

	Plane back_wall;
	back_wall.m_transform = translation(0, 0, 5) * rotation(DEG_90, 0.0, 0.0);
	back_wall.m_material.m_pattern = checkers_pattern(Color4(0.8, 0.8, 1.0), Color4(0.1, 0.1, 0.1));
	back_wall.m_material.m_specular = 0.0;
	w.add_object(back_wall);

	// === GLASS SPHERE (center) ===
	Sphere glass_sphere;
	glass_sphere.m_transform = translation(0, 1, 0);
	glass_sphere.m_material.m_pattern = no_pat(Color4(1, 1, 1));
	glass_sphere.m_material.m_ambient = 0.0;
	glass_sphere.m_material.m_diffuse = 0.1;
	glass_sphere.m_material.m_specular = 0.9;
	glass_sphere.m_material.m_shininess = 300.0;
	glass_sphere.m_material.m_reflective = 0.9;
	glass_sphere.m_material.m_transparency = 0.9;
	glass_sphere.m_material.m_refractive = 1.5;
	w.add_object(glass_sphere);

	// === REFLECTIVE METAL SPHERE (left) ===
	Sphere mirror_sphere;
	mirror_sphere.m_transform = translation(-2.5, 1, 0);
	mirror_sphere.m_material.m_pattern = no_pat(Color4(0.8, 0.8, 0.8));
	mirror_sphere.m_material.m_ambient = 0.0;
	mirror_sphere.m_material.m_diffuse = 0.1;
	mirror_sphere.m_material.m_specular = 0.9;
	mirror_sphere.m_material.m_shininess = 300.0;
	mirror_sphere.m_material.m_reflective = 1.0;
	w.add_object(mirror_sphere);

	// === RED SPHERE (right) ===
	Sphere red_sphere;
	red_sphere.m_transform = translation(2.5, 1, 0);
	red_sphere.m_material.m_pattern = no_pat(Color4(1, 0, 0));
	red_sphere.m_material.m_specular = 0.9;
	red_sphere.m_material.m_shininess = 200.0;
	w.add_object(red_sphere);
	s.world = w;

	return s;
}
