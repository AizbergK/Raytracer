#include "Helpers.hpp"
#include "Tuples.hpp"
#include "Matrix.hpp"
#include "ImgBuf.hpp"
#include "Shapes.hpp"
#include "PointLight.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Patterns.hpp"
#include "ObjParser.hpp"

class Scene {
public:
	World world;
	Camera camera;
};

Scene test_scene(int);

Scene refraction_ball_scene(int);
Scene reflection_scene(int);
Scene cornell_box_scene(int);
Scene tree_obj_scene(int);

int main()
{
	//Scene scene{ test_scene(2000) };

	//Scene scene{ refraction_ball_scene(2000) };
	//Scene scene{ reflection_scene(2000) };
	//Scene scene{ cornell_box_scene(2000) };
	Scene scene{ tree_obj_scene(2000) };

	render(scene.camera, scene.world, 5).writeBMP("C:\\Users\\atzbe\\Desktop\\bmps", true);
	
	scene.world.delete_objects();

	return 0;
}

Scene test_scene(int size)
{
	Scene s;

	Camera c{ size, size, DEG_45 };
	c.m_transform = view_transform(Point4(0.0, 4.0, -5.0), Point4(0.0, 0.0, 0.0), Vector4(0.0, 1.0, 0.0));
	s.camera = c;

	World w;

	Material mat;
	mat.m_ambient = 0.1;
	mat.m_diffuse = 0.9;
	mat.m_specular = 0.0;
	mat.m_shininess = 0.0;
	mat.m_reflective = 0;
	mat.m_refractive = 1.0;
	mat.m_pattern = no_pat(BLACK);

	//shapes
	Plane floor{ mat };
	w.add_object(floor);
	mat.m_pattern = no_pat(WHITE);

	Sphere s1{ mat, translation(0.0, 0.0, -1.0) * scaling(0.25, 0.25, 0.25) };

	Cylinder c1{ mat, translation(0.0, 0.0, -1.0) *  rotation(0.0, -DEG_30, 0.0) * rotation(0.0, 0.0, -DEG_90) * scaling(0.25, 1.0, 0.25) };
	c1.m_minimum = 0.0;
	c1.m_maximum = 1.0;
	c1.m_closed = true;

	Group side;

	Group hexagon{ translation(0.0, 1.5, -1.75) };
	w.add_object(hexagon);
	Group* p_hexagon = dynamic_cast<Group*>(*w.m_shapes.rbegin());
	for (int i = 0; i < 6; i++)
	{
		side.m_transform = rotation(0.0, DEG_60 * i, 0.0);
		p_hexagon->add_child(side);
		Group* p_side = dynamic_cast<Group*>(*p_hexagon->m_children.rbegin());
		p_side->add_child(s1);
		p_side->add_child(c1);
	}

	//Lights
	double tl_lght_int = 1.0;
	Light top_left{ Point4(-10.0, 10.0, -10.0), Color4(tl_lght_int, tl_lght_int, tl_lght_int) };
	w.add_light(top_left);
	s.world = w;

	return s;
}

Scene refraction_ball_scene(int size)
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

Scene reflection_scene(int size)
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

Scene cornell_box_scene(int size)
{
	Scene s;

	Camera c{ size, size , PI / 180.0 * 40.0 };
	c.m_transform = view_transform(Point4(278.0, 273.0, -800), Point4(278.0, 273.0, 0), Vector4(0.0, 1.0, 0.0));
	s.camera = c;

	World w;

	// === LIGHT ===
	Light one_light{ Point4(278.0, 548.8, 278.0), WHITE };
	w.add_light(one_light);

	Material wall_material;
	wall_material.m_ambient = 0.1;
	wall_material.m_diffuse = 0.9;
	wall_material.m_specular = 0.0;
	wall_material.m_shininess = 0.0;
	wall_material.m_reflective = 0.2;
	wall_material.m_refractive = 1.0;
	wall_material.m_pattern = no_pat(WHITE);

	// === WALLS  ===
	Plane floor{ wall_material };
	w.add_object(floor);

	Plane back{ wall_material, TRS(Point4(0.0, 0.0, 555.0), Point4(DEG_90, 0.0, 0.0)) };
	w.add_object(back);

	Plane ceil{ wall_material, TRS(Point4(0.0, 555.0, 0.0)) };
	w.add_object(ceil);

	wall_material.m_pattern = no_pat(RED);
	Plane left{ wall_material, TRS(Point4(0.0, 0.0, 0.0), Point4(0.0, 0.0, DEG_90)) };
	w.add_object(left);

	wall_material.m_pattern = no_pat(GREEN);
	Plane right{ wall_material, TRS(Point4(555.0, 0.0, 0.0), Point4(0.0, 0.0, DEG_90)) };
	w.add_object(right);

	// === BOXES ===
	Material cube_material = wall_material;
	//cube_material.m_reflective = 0.1;
	cube_material.m_pattern = no_pat(WHITE);

	Cube tall_box{ cube_material, TRS(Point4(178.5, 165, 308.5), Point4(0.0, -DEG_30 / 2.0, 0.0), Point4(165.0, 330.0, 165.0) / 2.0) };
	w.add_object(tall_box);
	//Cube short_box{ cube_material, TRS(Point4(378.5, 82.5, 178.5), Point4(0.0, DEG_30, 0.0), Point4(165.0, 165.0, 165.0) / 2.0) };
	//w.add_object(short_box);
	Sphere glass;
	glass.m_material.m_pattern = no_pat(Color4(1, 1, 1));
	glass.m_material.m_ambient = 0.0;
	glass.m_material.m_diffuse = 0.1;
	glass.m_material.m_specular = 0.9;
	glass.m_material.m_shininess = 300.0;
	glass.m_material.m_reflective = 0.9;
	glass.m_material.m_transparency = 0.9;
	glass.m_material.m_refractive = 1.5;

	glass.m_transform = TRS(Point4(378.5, 82.5, 178.5), Point4(0.0, DEG_30, 0.0), Point4(165.0, 165.0, 165.0) / 2.0);
	w.add_object(glass);

	s.world = w;

	return s;
}

Scene tree_obj_scene(int size)
{
	Scene s;

	Camera c{ size, size, DEG_45 };
	c.m_transform = view_transform(Point4(0.0, 5.0, -6.0), Point4(0.0, 2.0, 0.0), Vector4(0.0, 1.0, 0.0));
	s.camera = c;

	World w;
	ObjParser op;
	w.add_object(op.parse("C:\\Users\\atzbe\\Desktop\\Lowpoly_tree_sample.obj"));
	w.m_shapes[0]->m_transform = TRS(Point4(-0.3, 0.0, 0.0), Point4(0.0, 0.0, 0.0), Point4(0.16, 0.16, 0.16));

	Plane floor{ WHITE, TRS(Point4(0.0, 0.0, 0.0), Point4(0.0, 0.0, 0.0))};
	w.add_object(floor);

	//Lights
	double tl_lght_int = 1.0;
	Light top_left{ Point4(-10.0, 10.0, -10.0), Color4(tl_lght_int, tl_lght_int, tl_lght_int) };
	w.add_light(top_left);
	s.world = w;

	return s;
}