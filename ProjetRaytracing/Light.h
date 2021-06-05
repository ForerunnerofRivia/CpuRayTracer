#pragma once

#include "vec3.h"
#include "Objet.h"

class Light_c : public Objet_c {
public:
	float attenuation;
	float intensity;
	Light_c(vec3 pos, float intensity, float attenuation);
};