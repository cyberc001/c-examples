#include "vec2.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "htable_oa.h"
DEF_HTABLE_OA(func, const char*, void*);
size_t func_hash_func(size_t table_sz, const char** _key)
{
	const char* key = *_key;
	size_t h = 0;
	for(; *key; ++key) { h *= 256; h %= table_sz; h += *key; }
	return h % table_sz;
}
int func_cmp_func(const char** k1, const char** k2)
{
	return strcmp(*k1, *k2);
}
// ----------------------------------------------------------------------

static double _vec2d_length(const vec2d* self);


static htable_oa_func _vtable;
void vec2d_init()
{
	htable_oa_func_create(&_vtable, 8, func_hash_func, func_cmp_func);
	htable_oa_func_insert(&_vtable, "length", _vec2d_length);
}

vec2d* vec2d_new(double x, double y)
{
	vec2d* v = malloc(sizeof(vec2d));
	v->x = x; v->y = y;

	v->vtable = &_vtable;

	return v;
}

double vec2d_length(const vec2d* self)
{
	double (*length)(const vec2d* self) =
			*htable_oa_func_find((htable_oa_func*)self->vtable, "length");
	return length(self);
}
static double _vec2d_length(const vec2d* self)
{
	return sqrt(self->x * self->x + self->y * self->y);
}
