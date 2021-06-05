#pragma once
#include "Mat.h"
#include "Ray.h"
#include "vec3.h"
#include "FreeImage/FreeImage.h"

class Sphere_c {
public:
	vec3 Pos;
	float Rayon;
	Mat_c texture;
	RGBQUAD color;

	Sphere_c(vec3 Pos,float R, RGBQUAD color);
	Sphere_c(vec3 Pos, float R, Mat_c texture);
	vec3 get_normal(vec3 p);
};
