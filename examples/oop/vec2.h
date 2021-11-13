#ifndef VEC2_H
#define VEC2_H

typedef struct _vec2d{
	const void* vtable;
	double x, y;
} vec2d;

void vec2d_init();

vec2d* vec2d_new(double x, double y);
double vec2d_length(const vec2d* self);

#endif
