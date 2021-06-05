#ifndef VEC3_H
#define VEC3_H


#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include<vector>

#ifdef _LIB_C_
	#define LIB_API __declspec(dllexport)
#else
	#define LIB_API __declspec(dllimport)
#endif


/*! \file vecteur.h
\brief Header de notre librairie.
*/


//!  Structure vecteur
/*!
Tous les vecteurs que nous utiliserons seront d�finies par 3 composantes x, y, z.
*/
typedef struct vect3_s
{
	float x;
	float y;
	float z;
}vec3;


/*! \brief Cr�ation d'un vecteur

Fonction qui cr�er un vecteur 3D � partir des trois r�els en param�tres

\param[in] x Composante x du vecteur
\param[in] y Composante y du vecteur
\param[in] z Composante z du vecteur

\return Retourne le vecteur 3D initialis�
*/
LIB_API vec3 set3(float x, float y, float z);


/*! \brief Addition de deux vecteurs

Fonction qui additionne les deux vecteurs en param�tre

\param[in] v1 Premier vecteur
\param[in] v2 Deuxi�me vecteur

\return Retourne l'addition des deux vecteurs
*/
LIB_API vec3 add3(vec3 v1, vec3 v2);


/*! \brief Soustraction de deux vecteurs

Fonction qui soustrait les deux vecteurs en param�tre

\param[in] v1 Premier vecteur
\param[in] v2 Deuxi�me vecteur

\return Retourne la soustraction des deux vecteurs
*/
LIB_API vec3 sub3(vec3 v1, vec3 v2);


/*! \brief Multiplication d'un vecteur par un scalaire

Fonction qui multiplie le vecteur en param�tre par le scalaire en param�tre

\param[in] v Vecteur que vous souhaitez multiplier
\param[in] s R�el correspondant au scalaire par lequel vous souhaitez multiplier votre vecteur

\return Retourne un nouveau vecteur correspondant � la multiplication du vecteur par le scalaire
*/
LIB_API vec3 mul3(vec3 v, float s);


/*! \brief Division d'un vecteur par un scalaire

Fonction qui divise le vecteur en param�tre par le scalaire en param�tre

\param[in] v R�el Vecteur que vous souhaitez diviser
\param[in] s R�el correspondant au scalaire par lequel vous souhaitez diviser votre vecteur

\return Retourne un nouveau vecteur correspondant � la division du vecteur par le scalaire
*/
LIB_API vec3 div3(vec3 v, float s);


/*! \brief Calcul de la norme

Fonction qui renvoie la norme du vecteur en param�tre

\param[in] v Vecteur dont on souhaite obtenir la norme

\return Retourne le r�el correspondant � la norme du vecteur en param�tre
*/
LIB_API float norm3(vec3 v);


/*! \brief Normalisation d'un vecteur

Fonction qui normalise le vecteur en param�tre

\param[in/out] v Vecteur qu'on souhaite normaliser

\return Retourne le vecteur normaliz�
*/
LIB_API vec3 normalize3(vec3 v);


/*! \brief Calcul de la distance entre deux vecteurs

Fonction qui renvoie la distance qui s�pare les deux vecteurs

\param[in] v1 Premier vecteur
\param[in] v2 Deuxi�me vecteur

\return Retourne le scalaire correspondant � la distance entre les deux vecteurs
*/
LIB_API float distance3(vec3 v1, vec3 v2);


/*! \brief Produit scalaire

Fonction qui effectue le produit scalaire de deux vecteurs

\param[in] v1 Premier vecteur
\param[in] v2 Deuxi�me vecteur

\return Retourne un vecteur correspondant au produit scalaire des deux vecteurs en param�tre
*/
LIB_API float dot3(vec3 v1, vec3 v2);


/*! \brief Produit vectoriel

Fonction qui effectue le produit vectoriel de deux vecteurs

\param[in] v1 Premier vecteur
\param[in] v2 Deuxi�me vecteur

\return Retourne un vecteur correspondant au produit vectoriel des deux vecteurs en param�tre
*/
LIB_API vec3 cross3(vec3 v1, vec3 v2);


/*! \brief Copie d'un vecteur

Fonction qui effectue la copie d'un vecteur

\param[in] v1 Vecteur que l'on souhaite copier

\return Retourne le copie du vecteur pass� en param�tre
*/
LIB_API vec3 copy3(vec3 v);


/*! \brief Reflet d'un vecteur

Fonction qui donne le reflet d'un vecteur par rapport � sa normale

\param[in] v Vecteur dont on souhaite obtenir le reflet
\param[in] n Normale du vecteur dont on souhaite obtenir le reflet

\return Retourne le vecteur reflet du vecteur pass� en param�tre
*/
LIB_API vec3 reflect3(vec3 v, vec3 n);


#endif