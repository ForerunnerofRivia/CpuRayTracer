#pragma once
#include "Objet.h"
#include "vec3.h"

typedef struct reso {
	int width;
	int height;
}reso;

class Camera_c : public  Objet_c {
public:
	int focale;
	reso resolution;
	vec3 rot;


	Camera_c(reso resolution, float focale, vec3 rot, vec3 pos);

};













































