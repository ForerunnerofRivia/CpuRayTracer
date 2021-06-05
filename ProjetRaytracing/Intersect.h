#pragma once

#include "vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "Scene.h"


class Intersection_c {
public:
	vec3 position;	//ou est l'intersection
	Sphere_c * Spehreintersectionner; //avec quel objet?
	vec3 vecprimaire;
	vec3 vecreflect;
	Intersection_c(vec3 pos, Sphere_c * sphere, vec3 vecprimaire);
};


struct solution_s{
	Sphere_c* Sphere;
	float intersect;
	vec3 s1;
	vec3 s2;
};

Intersection_c* UniIsIntersect(Ray_c Rayon, Scene_c myScene, vec3 origin);
solution_s calc2equa(Ray_c Ray, Sphere_c * Sphere);
RGBQUAD isIlluminate(Intersection_c intersection, Scene_c Scene);
BOOL IsIntersectLight(Ray_c Rayon, Scene_c myScene);
BOOL pointInFrontof(vec3 direction, vec3 direction2);
BOOL vecdiff(vec3 a, vec3 b);
BOOL isSvalable(Ray_c Ray, vec3 solution);