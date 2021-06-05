#include "Sphere.h"

Sphere_c::Sphere_c(vec3 Pos, float R, RGBQUAD color) {
	
	this->Pos = Pos;
	this->Rayon = R;
	this->color = color;
}

vec3 Sphere_c::get_normal(vec3 p) {
	vec3 a = sub3(p, this->Pos);
	return mul3(a, -1 / this->Rayon);
}