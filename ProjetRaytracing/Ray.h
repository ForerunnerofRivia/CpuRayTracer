#pragma once

#include "vec3.h"
#include "Objet.h"
#include "Camera.h"

class Ray_c{
public:
	vec3 depart;
	vec3 fin;
	vec3 direction;


	Ray_c(vec3 firstPos, vec3 secondPos);
	Ray_c(vec3 firstpos, vec3 direction, int reflect);
	vec3 getDirection();
	vec3 getOrigin();

};