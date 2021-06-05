#include "Ray.h"

Ray_c::Ray_c(vec3 firstpos, vec3 secondPos) {
	this->depart = firstpos;
	this->fin = secondPos;
	this->direction = sub3(secondPos, firstpos);
}

Ray_c::Ray_c(vec3 firstpos, vec3 direction, int reflect) {
	this->depart = firstpos;
	this->fin = add3(firstpos, direction);
	this->direction = direction;
}

vec3 Ray_c::getDirection() {
	return this->direction;
}

vec3 Ray_c::getOrigin() {
	return this->depart;
}