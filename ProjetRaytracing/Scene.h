#pragma once
#include <list>
#include "vec3.h"
#include "Light.h"
#include "Sphere.h"


class Scene_c {
public:
	std::list<Light_c> lightlist;
	std::list<Sphere_c> SphereList;
	RGBQUAD backgroundColor;

	Scene_c();
};