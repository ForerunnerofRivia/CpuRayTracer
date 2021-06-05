#define _LIB_C_

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"vec3.h"



LIB_API vec3 set3(float x, float y, float z)
{
	vec3 v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}


LIB_API vec3 add3(vec3 v1, vec3 v2)
{
	vec3 v3;
	v3.x = v1.x + v2.x;
	v3.y = v1.y + v2.y;
	v3.z = v1.z + v2.z;
	return v3;
}


LIB_API vec3 sub3(vec3 v1, vec3 v2)
{
	vec3 v3;
	v3.x = v1.x - v2.x;
	v3.y = v1.y - v2.y;
	v3.z = v1.z - v2.z;
	return v3;
}


LIB_API vec3 mul3(vec3 v, float s)
{
	vec3 v1;
	v1.x = s * v.x;
	v1.y = s * v.y;
	v1.z = s * v.z;

	return v1;
}


LIB_API vec3 div3(vec3 v, float s)
{
	if (s == 0)
	{
		return v;
	}
	vec3 v1;
	v1.x = v.x / s;
	v1.y = v.y / s;
	v1.z = v.z / s;

	return v1;
}


LIB_API float norm3(vec3 v)
{
	float a = pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2);
	return sqrt(a);
}


LIB_API vec3 normalize3(vec3 v)
{
	float norm = norm3(v);
	v = div3(v, norm);
	return v;
}


LIB_API float distance3(vec3 v1, vec3 v2)
{
	float deltx = v2.x - v1.x;
	float delty = v2.y - v1.y;
	float deltz = v2.z - v1.z;
	float puissance = pow(deltx, 2) + pow(delty, 2) + pow(deltz, 2);
	puissance = sqrt(puissance);
	return puissance;
}


LIB_API float dot3(vec3 v1, vec3 v2)
{
	float res = v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
	return res;
}


LIB_API vec3 cross3(vec3 v1, vec3 v2)
{
	vec3 v;
	v.x = (v1.y * v2.z) - (v1.z * v2.y);
	v.y = -((v1.x * v2.z) - (v1.z * v2.x));
	v.z = (v1.x * v2.y) - (v1.y * v2.x);
	return v;
}


LIB_API vec3 copy3(vec3 v)
{
	vec3 copy;
	copy.x = v.x;
	copy.y = v.y;
	copy.z = v.z;
	return copy;
}


LIB_API vec3 reflect3(vec3 v, vec3 n)
{
	vec3 r;
	int tmp = 2*(dot3(v, n));
	r = mul3(n, tmp);
	r = sub3(r, v);
	return r;
}