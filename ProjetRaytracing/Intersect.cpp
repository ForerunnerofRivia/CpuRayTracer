#include "Intersect.h"
#include "vec3.h"
#include "Mat.h"
#define DepthField 2000




Intersection_c::Intersection_c(vec3 pos, Sphere_c* Sphere, vec3 vecprimaire) {
	this->position = pos;
	this->Spehreintersectionner = Sphere;
	this->vecprimaire = vecprimaire;
}

Intersection_c* UniIsIntersect(Ray_c Rayon, Scene_c myScene, vec3 origin) { //retourne l'intersection la plus proche ou rien;

	float i = 0;
	float min = 50000;
	int minimum;
	float current = 10000.f;
	int k = 0;
	int j = 0;
	solution_s solution;
	std::vector<solution_s> listsolution;
	float current2 = 0.f;
	int s1s2 = -1;


	std::list<Sphere_c>::iterator it;
	for (it = myScene.SphereList.begin(); it != myScene.SphereList.end(); ++it) {	//test d'intersection pour les spheres
		Sphere_c* crSphere = new Sphere_c(it->Pos, it->Rayon, it->color);
		solution = calc2equa(Rayon, crSphere);
		if (solution.intersect == 0) {
			continue;
		}
		else {
			listsolution.push_back(solution);
		}
	}

	//vire les resultats nonvalable

	std::vector<solution_s>::iterator at;
	for (at = listsolution.begin(); at != listsolution.end(); ++at) {
		if (at->intersect == 1) {
			if (!vecdiff(Rayon.depart, at->s1) || !pointInFrontof(sub3(Rayon.depart, at->s1), Rayon.direction)) {	// pas valable
				at = listsolution.erase(at);
			}
		}
		else
		{
			if (!isSvalable(Rayon, at->s1) && isSvalable(Rayon, at->s2)) {	// s1 pas valable mais s2 valable
				at->intersect = 1;
				at->s1 = at->s2;
			}
			else if (isSvalable(Rayon, at->s1) && !isSvalable(Rayon, at->s2)) {	// s2 pas valable mais s1 valable
				at->intersect = 1;
			}
			else if (!isSvalable(Rayon, at->s1) && !isSvalable(Rayon, at->s2)) { //aucun des deux valables
				at->intersect = 0;
			}
		}
	}

	//Test de la solution la plus proche

	if (listsolution.size() == 0) {
		return NULL;
	}
	else if (listsolution.size() > 0) {
		for (k = 0; k < listsolution.size(); k++) {
			current2 = 10000.f;
			if (listsolution[k].intersect == 1) {
				current = distance3(listsolution[k].s1, origin);
			}
			else if (listsolution[k].intersect == 2) {
				current = distance3(listsolution[k].s1, origin);
				current2 = distance3(listsolution[k].s2, origin);
			}
			else {
				continue;
			}


			if (current < min) {
				min = current;
				minimum = k;
				s1s2 = 1;
			}
			if (listsolution[k].intersect == 2 && current2 < min) {
				min = current2;
				minimum = k;
				s1s2 = 2;
			}
		}

		//Renvoies la solution la plus proche ou NULL
		if (s1s2 == 1) {
			Intersection_c* intersection = new Intersection_c(listsolution[minimum].s1, listsolution[minimum].Sphere, Rayon.direction);
			return intersection;
		}
		else if (s1s2 == 2) {
			Intersection_c* intersection = new Intersection_c(listsolution[minimum].s2, listsolution[minimum].Sphere, Rayon.direction);
			return intersection;
		}
		else {
			return NULL;
		}


	}
	return NULL;
}

BOOL isSvalable(Ray_c Ray, vec3 solution) {					//Return True si valable faux sinon.
	if (vecdiff(solution, Ray.depart) && (pointInFrontof(sub3(solution, Ray.depart), Ray.direction))) {
		return true;
	}
	return false;
}

BOOL IsIntersectLight(Ray_c Rayon, Scene_c myScene) { //Vrai si le rayon est secant à une sphere, faux sinon.

	float i = 0;
	solution_s solution;
	std::vector<solution_s> listsolution;



	std::list<Sphere_c>::iterator it;			//parcour des objets dans la scnes ici seulement des spheres
	for (it = myScene.SphereList.begin(); it != myScene.SphereList.end(); ++it) {

		Sphere_c* crSphere = new Sphere_c(it->Pos, it->Rayon, it->color);
		solution = calc2equa(Rayon, crSphere);
		if (solution.intersect == 0) {
			continue;
		}
		else {
			listsolution.push_back(solution);
		}
	}

	if (listsolution.size() == 0) {
		return false;
	}

	for (i = 0; i < listsolution.size(); i++) {		//Parcours les solutions et verifie si elle sont valables, si elles le sont return true sinon false
		if (listsolution[i].intersect == 1) {
			if (isSvalable(Rayon, listsolution[i].s1)) {
				return true;
			}
		}
		else if (listsolution[i].intersect == 2) {

			if (isSvalable(Rayon, listsolution[i].s1)) {
				return true;
			}
			else if (isSvalable(Rayon, listsolution[i].s2)) {
				return true;
			}
		}

	}


	return false;

}

BOOL vecdiff(vec3 a, vec3 b) {						//Renvois Vrai si les solution ici sous forme de vecteurs sont differentes, Faux Sinon. Le cast en int permet de corriger les differences minime entre deux meme solutions.


	if ((int)a.x != (int)b.x || (int)a.y != (int)b.y || (int)a.z != (int)b.z) {
		return true;
	}
	else {
		return false;
	}
}

BOOL pointInFrontof(vec3 direction, vec3 direction2) { //Renvoi True si les deux vecteurs sont dans la meme direction, False sinon.
	float dot = dot3(direction, direction2);
	if (dot < 0) {
		return false;
	}
	else {
		return true;
	}
}



solution_s calc2equa(Ray_c Ray, Sphere_c* Sphere) { //Renvois la/les solution(s) de l'equation de second degrée à l'intersection d'une sphere et d'un rayon
	float a = 0.f;
	float b = 0.f;
	float b1 = 0.f;
	float b2 = 0.f;
	float b3 = 0.f;
	float c = 0.f;
	float delta = 0.f;
	float d1 = 0.f;
	float d2 = 0.f;
	solution_s solution;

	a = pow((Ray.fin.x - Ray.depart.x), 2) + pow((Ray.fin.y - Ray.depart.y), 2) + pow((Ray.fin.z - Ray.depart.z), 2);

	b1 = (Ray.fin.x - Ray.depart.x) * (Ray.depart.x - Sphere->Pos.x);
	b2 = (Ray.fin.y - Ray.depart.y) * (Ray.depart.y - Sphere->Pos.y);
	b3 = (Ray.fin.z - Ray.depart.z) * (Ray.depart.z - Sphere->Pos.z);

	b = 2 * (b1 + b2 + b3);

	c = pow((Ray.depart.x - Sphere->Pos.x), 2) + pow((Ray.depart.y - Sphere->Pos.y), 2) + pow((Ray.depart.z - Sphere->Pos.z), 2) - pow(Sphere->Rayon, 2);

	delta = pow(b, 2) - 4 * a * c;

	if (delta < 0) {															//Utilisation de la structure solution_s permettant d'uniformiser le resultat malgres les delta
		solution.intersect = 0;
		solution.Sphere = Sphere;
		return solution;
	}
	else if (delta == 0) {
		solution.intersect = 1;
		d1 = ((-1) * b) / (2 * a);
		solution.s1.x = Ray.depart.x + d1 * (Ray.fin.x - Ray.depart.x);
		solution.s1.y = Ray.depart.y + d1 * (Ray.fin.y - Ray.depart.y);
		solution.s1.z = Ray.depart.z + d1 * (Ray.fin.z - Ray.depart.z);
		solution.Sphere = Sphere;
		return solution;
	}
	else {
		solution.intersect = 2;
		d1 = (-b - sqrt(delta)) / (2 * a);
		d2 = (-b + sqrt(delta)) / (2 * a);
		solution.s1.x = Ray.depart.x + d1 * (Ray.fin.x - Ray.depart.x);
		solution.s1.y = Ray.depart.y + d1 * (Ray.fin.y - Ray.depart.y);
		solution.s1.z = Ray.depart.z + d1 * (Ray.fin.z - Ray.depart.z);

		solution.s2.x = Ray.depart.x + d2 * (Ray.fin.x - Ray.depart.x);
		solution.s2.y = Ray.depart.y + d2 * (Ray.fin.y - Ray.depart.y);
		solution.s2.z = Ray.depart.z + d2 * (Ray.fin.z - Ray.depart.z);

		solution.Sphere = Sphere;

		return solution;
	}
}







RGBQUAD isIlluminate(Intersection_c intersection, Scene_c Scene) { // Renvoie la couleur pour un pixel en fonction des lumieres et reflets

	RGBQUAD colorpixel = intersection.Spehreintersectionner->color;
	float distance;
	Intersection_c* interreflect = NULL;
	std::list<Light_c>::iterator it;
	double diffuse = 0.f, specular = 0.f;
	for (it = Scene.lightlist.begin(); it != Scene.lightlist.end(); ++it) {
		Ray_c* crRay = new Ray_c(intersection.position, it->Position);		//Crée un rayon entre l'intersection et les lumiere

		if (!(IsIntersectLight(*crRay, Scene))) {					//Si il n'y a pas de sphere secante au rayon

			// REFLECTION
			vec3 reflection = reflect3(crRay->direction, intersection.Spehreintersectionner->get_normal(intersection.position));		//Calcule du reflet
			Ray_c* RayReflect = new Ray_c(intersection.position, reflection, 2);
			interreflect = UniIsIntersect(*RayReflect, Scene, RayReflect->depart);							//Regarde si le reflet est secant avec une sphere
			if (interreflect) {																				// Si sécant renvois la couleur de cette derniere
				//std::cout << interreflect << std::endl;
				colorpixel.rgbRed = interreflect->Spehreintersectionner->color.rgbRed;
				colorpixel.rgbGreen = interreflect->Spehreintersectionner->color.rgbGreen;
				colorpixel.rgbBlue = interreflect->Spehreintersectionner->color.rgbBlue;
				colorpixel.rgbReserved = interreflect->Spehreintersectionner->color.rgbReserved;
				return colorpixel;
			}
			else {																								//Si le reflet nest sécant avec aucun objet (pas de reflet)
				//diffuse
				diffuse = -dot3(intersection.Spehreintersectionner->get_normal(intersection.position), sub3(it->Position, intersection.position));		//Utilisation de Blinn-Phong
				diffuse = DIFUSE * diffuse > 0 ? diffuse : 0.f;

				//specular

				vec3 median = normalize3(add3(mul3((intersection.vecprimaire), -1), sub3(it->Position, intersection.position)));
				specular = pow(dot3(intersection.Spehreintersectionner->get_normal(intersection.position), median), 100.f);
				specular = SPECULAR * specular > 0 ? specular : 0.f;
				float lux = (float)(AMBIENT + diffuse);
				lux = lux > 1.0f ? 1.0f : lux;

				int r = int(colorpixel.rgbRed * lux + 255 * specular);
				int g = int(colorpixel.rgbGreen * lux + 255 * specular);
				int b = int(colorpixel.rgbBlue * lux + 255 * specular);

				colorpixel.rgbRed = BYTE(r > 255 ? 255 : r);
				colorpixel.rgbGreen = BYTE(g > 255 ? 255 : g);
				colorpixel.rgbBlue = BYTE(b > 255 ? 255 : b);



				return colorpixel;
			}
		}
		else {																			// Si il y a au moin une sphere sécante au rayon
			colorpixel = intersection.Spehreintersectionner->color;
			float lux = (float)(AMBIENT + diffuse);
			lux = lux > 1.0f ? 1.0f : lux;

			int r = int(colorpixel.rgbRed * lux + 255 * specular);
			int g = int(colorpixel.rgbGreen * lux + 255 * specular);
			int b = int(colorpixel.rgbBlue * lux + 255 * specular);

			colorpixel.rgbRed = BYTE(r > 255 ? 255 : r);
			colorpixel.rgbGreen = BYTE(g > 255 ? 255 : g);
			colorpixel.rgbBlue = BYTE(b > 255 ? 255 : b);



			return colorpixel;
		}
	}
}
