#ifndef VEC3_H
#define VEC3_H

#include "vec2.h"

typedef struct _vec3d
{
	struct _vec2d;
	double z;
} vec3d;

void vec3d_init();

vec3d* vec3d_new(double x, double y, double z);
double vec3d_length(const vec3d* self);

#endif
