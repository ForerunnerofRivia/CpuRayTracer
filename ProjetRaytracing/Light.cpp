#include "Light.h"

Light_c::Light_c(vec3 Pos, float intensity, float attenuation) {
	this->attenuation = attenuation;
	this->intensity = intensity;
	this->Position = Pos;
}

