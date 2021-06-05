#include "vec3.h"
#include "FreeImage/FreeImage.h"
#include "Sphere.h"
#include "Camera.h"
#include "Intersect.h"
#include "Scene.h"

#define RESOX 500
#define RESOY 500

void mainloop(Scene_c myScene, FIBITMAP* img, Camera_c* myCamera);

void main()
{
	FreeImage_Initialise(true);

	std::cout << FreeImage_GetCopyrightMessage() << std::endl;
	std::cout << "FreeImage Version : " << FreeImage_GetVersion() << std::endl;
	// Construction de la scene
	RGBQUAD couleur;
	couleur.rgbBlue = 0;
	couleur.rgbGreen = 100;
	couleur.rgbRed = 255;
	couleur.rgbReserved = 0;

	RGBQUAD couleur2;
	couleur2.rgbBlue = 0;
	couleur2.rgbGreen = 0;
	couleur2.rgbRed = 255;
	couleur2.rgbReserved = 0;


	reso CamReso;
	CamReso.height = RESOY;
	CamReso.width = RESOX;
	vec3 camPos = set3(250, 250, -400);

	Scene_c* myScene = new Scene_c();
	myScene->backgroundColor.rgbBlue = 100;
	myScene->backgroundColor.rgbGreen = 100;
	myScene->backgroundColor.rgbRed = 100;
	myScene->backgroundColor.rgbReserved = 0;


	Camera_c* myCamera = new Camera_c(CamReso, 300, camPos, camPos);


	vec3 spherePos = set3(390, 375, 500);
	vec3 sphere2Pos = set3(105, 100, 400);

	Sphere_c* mySphere = new Sphere_c(spherePos, 200.0f, couleur);
	Sphere_c* mySphere2 = new Sphere_c(sphere2Pos, 200.0f, couleur2);

	myScene->SphereList.push_front(*mySphere);
	myScene->SphereList.push_front(*mySphere2);

	float fps = 30.f;

	FIMULTIBITMAP* multi = FreeImage_OpenMultiBitmap(FIF_GIF, "../Gen/RAYTRACED.gif", 1, 0);
	DWORD dwFrameTime = (DWORD)((1000.0f / fps) + 0.5f);

	double x1 = -200, y1 = 500, z1 = 350;

	for (int i = 0; i < 24; i++)						//Création du gif
	{
		system("cls");
		printf("File ready in :\t%d ", 24 - i);

		vec3 LightPos = set3(x1 += 20, y1 -= 5, z1 -= 5);
	
		Light_c* myLight = new Light_c(LightPos, 1.0f, 0.2f);


		if (!myScene->lightlist.empty())	myScene->lightlist.clear();
		myScene->lightlist.push_front(*myLight);
	

		FIBITMAP* img = FreeImage_Allocate(RESOX, RESOY, 3 * 8);
		mainloop(*myScene, img, myCamera);

		img = FreeImage_ColorQuantize(img, FIQ_WUQUANT);

		FreeImage_SetMetadata(FIMD_ANIMATION, img, NULL, NULL);
		FITAG* tag = FreeImage_CreateTag();
		if (tag) {
			FreeImage_SetTagKey(tag, "FrameTime");
			FreeImage_SetTagType(tag, FIDT_LONG);
			FreeImage_SetTagCount(tag, 1);
			FreeImage_SetTagLength(tag, 4);
			FreeImage_SetTagValue(tag, &dwFrameTime);
			FreeImage_SetMetadata(FIMD_ANIMATION, img, FreeImage_GetTagKey(tag), tag);
			FreeImage_DeleteTag(tag);
		}
		FreeImage_AppendPage(multi, img);

		FreeImage_Unload(img);
	}
	FreeImage_CloseMultiBitmap(multi);
}



void mainloop(Scene_c myScene, FIBITMAP* img, Camera_c* myCamera) { //Genere une image pour une Scene
	int i, j;
	float illumination = 0.2f;
	RGBQUAD color;
	for (j = 0; j < RESOY; j++) {
		for (i = 0; i < RESOX; i++) {		//pour chaque pixel
			vec3 crPixel = set3(i, j, 0);
			Ray_c* crRay = new Ray_c(myCamera->Position, crPixel);  //calcul du rayon primaire
			Intersection_c* myIntersection = UniIsIntersect(*crRay, myScene, myCamera->Position);

			if (myIntersection == NULL) { //pas d'intersection

				FreeImage_SetPixelColor(img, i, j, &myScene.backgroundColor);			//le pixel est noir
			}
			else { //une intersection
				color = isIlluminate(*myIntersection, myScene);
				
				FreeImage_SetPixelColor(img, i, j, &(color));
			}


		}
	}

}
