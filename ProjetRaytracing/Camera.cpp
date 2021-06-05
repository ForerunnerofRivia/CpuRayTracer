#include "Camera.h"


Camera_c::Camera_c(reso resolution, float focale, vec3 rot, vec3 pos) {
	this->resolution = resolution;
	this->focale = focale;
	this->rot = rot;
	this->Position = pos;
}