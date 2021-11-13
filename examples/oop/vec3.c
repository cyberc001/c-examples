#include "vec3.h"
#include <math.h>
#include <stdlib.h>

#include "htable_oa.h"
DEF_HTABLE_OA(func1, const char*, void*);
size_t func_hash_func1(size_t table_sz, const char** _key)
{
	const char* key = *_key;
	size_t h = 0;
	for(; *key; ++key) { h *= 256; h %= table_sz; h += *key; }
	return h % table_sz;
}
int func_cmp_func1(const char** k1, const char** k2)
{
	return strcmp(*k1, *k2);
}
// -------------------------------------------

static double _vec3d_length(const vec3d* self);

static htable_oa_func1 _vtable;
void vec3d_init()
{
	htable_oa_func1_create(&_vtable, 8, func_hash_func1, func_cmp_func1);
	htable_oa_func1_insert(&_vtable, "length", _vec3d_length);
}

vec3d* vec3d_new(double x, double y, double z)
{
	vec3d* v = malloc(sizeof(vec3d));
	v->x = x; v->y = y; v->z = z;

	v->vtable = &_vtable;

	return v;
}

double vec3d_length(const vec3d* self)
{
	double (*length)(const vec3d* self) =
			*htable_oa_func1_find((htable_oa_func1*)self->vtable, "length");
	return length(self);
}
static double _vec3d_length(const vec3d* self)
{
	return sqrt(self->x * self->x + self->y * self->y + self->z * self->z);
}
