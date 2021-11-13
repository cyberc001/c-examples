#ifndef HTABLE_OA_H
#define HTABLE_OA_H

#include <stdlib.h>
#include <string.h>

#define HTABLE_OA_TYPE(tname) htable_oa_ ## tname

#define DEF_HTABLE_OA_STRUCT(tname, K, V)\
typedef struct{\
	size_t size;\
	V * data;\
	K * keys;\
	size_t free_bitmap_sz;\
	size_t* free_bitmap;\
	size_t (*hash_func)(size_t table_sz, const K* el);\
	int (*cmp_func) (const K* el1, const K* el2);\
} HTABLE_OA_TYPE(tname);

#define DEF_HTABLE_OA_CONSTRUCTOR(tname, K, V)\
void htable_oa_ ## tname ## _create(HTABLE_OA_TYPE(tname) * self, size_t size,\
				size_t (*hash_func)(size_t table_sz, const K* el),\
				int (*cmp_func)(const K* el1, const K* el2))\
{\
	self->size = size;\
	self->data = malloc(sizeof(V) * size);\
	self->keys = malloc(sizeof(K) * size);\
	size_t epbb = sizeof(size_t) * 8;\
	self->free_bitmap_sz = size / epbb + !!(size % epbb);\
	self->free_bitmap = malloc(self->free_bitmap_sz * sizeof(size_t));\
	memset(self->free_bitmap, 0, self->free_bitmap_sz * sizeof(size_t));\
	self->hash_func = hash_func;\
	self->cmp_func = cmp_func;\
}

#define DEF_HTABLE_OA_DESTRUCTOR(tname, K, V)\
void htable_oa_ ## tname ## _destroy(HTABLE_OA_TYPE(tname) * self)\
{\
	free(self->data);\
	free(self->keys);\
	free(self->free_bitmap);\
}

#define DEF_HTABLE_OA_IS_ALLOCATED(tname, K, V)\
int htable_oa_ ## tname ## _is_allocated(HTABLE_OA_TYPE(tname) * self, size_t i)\
{\
	size_t epbb = sizeof(size_t) * 8;\
	return self->free_bitmap[i / epbb] & (1 << (epbb - 1 - i % epbb));\
}
#define DEF_HTABLE_OA_SET_ALLOCATED(tname, K, V)\
void htable_oa_ ## tname ## _set_allocated(HTABLE_OA_TYPE(tname) * self, size_t i, int state)\
{\
	size_t epbb = sizeof(size_t) * 8;\
	if(state)\
		self->free_bitmap[i / epbb] |= (1 << (epbb - 1 - i % epbb));\
	else\
		self->free_bitmap[i / epbb] &= ~(1 << (epbb - 1 - i % epbb));\
}

#define DEF_HTABLE_OA_INSERT(tname, K, V)\
int htable_oa_ ## tname ## _insert(HTABLE_OA_TYPE(tname) * self, K key, V el)\
{\
	size_t h = self->hash_func(self->size, &key);\
	size_t i;\
	for(i = h; i < self->size && htable_oa_ ## tname ## _is_allocated(self, i); ++i) {}\
	if(i < self->size){\
		self->data[i] = el;\
		self->keys[i] = key;\
		htable_oa_ ## tname ## _set_allocated(self, i, 1);\
		return 1;\
	}\
	for(i = 0; i < h && htable_oa_ ## tname ## _is_allocated(self, i); ++i) {}\
	if(i < h){\
		self->data[i] = el;\
		self->keys[i] = key;\
		htable_oa_ ## tname ## _set_allocated(self, i, 1);\
		return 1;\
	}\
	return 0;\
}

#define DEF_HTABLE_OA_FIND(tname, K, V)\
const V * htable_oa_ ## tname ## _find(HTABLE_OA_TYPE(tname) * self, K key)\
{\
	size_t h = self->hash_func(self->size, &key);\
	size_t i;\
	if(self->cmp_func)\
		for(i = h; i < self->size\
			&& htable_oa_ ## tname ## _is_allocated(self, i)\
			&& self->cmp_func(&self->keys[i], &key);\
			 ++i) {}\
	else\
		for(i = h; i < self->size\
			&& htable_oa_ ## tname ## _is_allocated(self, i)\
			&& self->keys[i] != key;\
			 ++i) {}\
	\
	if(i < self->size && htable_oa_ ## tname ## _is_allocated(self, i))\
		return &self->data[i];\
	if(!htable_oa_ ## tname ## _is_allocated(self, i))\
		return NULL;\
	\
	if(self->cmp_func)\
		for(i = 0; i < h\
			&& htable_oa_ ## tname ## _is_allocated(self, i)\
			&& self->cmp_func(&self->keys[i], &key); ++i) {}\
	else\
		for(i = 0; i < h\
			&& htable_oa_ ## tname ## _is_allocated(self, i)\
			&& self->keys[i] != key; ++i) {}\
	if(i < h && htable_oa_ ## tname ## _is_allocated(self, i)){\
		return &self->data[i];\
	}\
	return NULL;\
}

#define DEF_HTABLE_OA_DELETE(tname, K, V)\
void htable_oa_ ## tname ## _delete(HTABLE_OA_TYPE(tname) * self, K key)\
{\
	size_t h = self->hash_func(self->size, &key);\
	size_t i;\
	if(self->cmp_func)\
		for(i = h; i < self->size\
			&& htable_oa_ ## tname ## _is_allocated(self, i)\
			&& self->cmp_func(&self->keys[i], &key);\
			 ++i) {}\
	else\
		for(i = h; i < self->size\
			&& htable_oa_ ## tname ## _is_allocated(self, i)\
			&& self->keys[i] != key;\
			 ++i) {}\
	\
	if(i < self->size && htable_oa_ ## tname ## _is_allocated(self, i)){\
		size_t j;\
		for(j = i; j < self->size\
			&& htable_oa_ ## tname ## _is_allocated(self, j)\
			&& self->hash_func(self->size, &self->keys[j]) == h;\
			++j) {}\
		--j;\
		htable_oa_ ## tname ## _set_allocated(self, j, 0);\
		memmove(&self->keys[i], &self->keys[i+1], (j - i) * sizeof(K));\
		memmove(&self->data[i], &self->data[i+1], (j - i) * sizeof(V));\
	}\
	if(!htable_oa_ ## tname ## _is_allocated(self, i))\
		return;\
	\
	if(self->cmp_func)\
		for(i = 0; i < h\
			&& htable_oa_ ## tname ## _is_allocated(self, i)\
			&& self->cmp_func(&self->keys[i], &key); ++i) {}\
	else\
		for(i = 0; i < h\
			&& htable_oa_ ## tname ## _is_allocated(self, i)\
			&& self->keys[i] != key; ++i) {}\
	\
	if(i < h && htable_oa_ ## tname ## _is_allocated(self, i)){\
		size_t j;\
		for(j = i; j < self->size\
			&& htable_oa_ ## tname ## _is_allocated(self, j)\
			&& self->hash_func(self->size, &self->keys[j]) == h;\
			++j) {}\
		--j;\
		htable_oa_ ## tname ## _set_allocated(self, j, 0);\
		memmove(&self->keys[i], &self->keys[i+1], (j - i) * sizeof(K));\
		memmove(&self->data[i], &self->data[i+1], (j - i) * sizeof(V));\
	}\
}

#define DEF_HTABLE_OA_REBUILD(tname, K, V)\
void htable_oa_ ## tname ## _rebuild(HTABLE_OA_TYPE(tname) * self, size_t new_sz)\
{\
	size_t old_size = self->size;\
	self->size = new_sz;\
	\
	V * old_data = self->data;\
	K * old_keys = self->keys;\
	self->data = malloc(sizeof(V) * self->size);\
	self->keys = malloc(sizeof(K) * self->size);\
	\
	size_t* old_free_bitmap = self->free_bitmap;\
	size_t epbb = sizeof(size_t) * 8;\
	self->free_bitmap_sz = self->size / epbb + !!(self->size % epbb);\
	self->free_bitmap = malloc(self->free_bitmap_sz * sizeof(size_t));\
	memset(self->free_bitmap, 0, self->free_bitmap_sz * sizeof(size_t));\
	\
	for(size_t i = 0; i < old_size; ++i){\
		if(old_free_bitmap[i / epbb] & (1 << (epbb - 1 - i % epbb)))\
			htable_oa_ ## tname ## _insert(self, old_keys[i], old_data[i]);\
	}\
	free(old_data);\
	free(old_keys);\
	free(old_free_bitmap);\
}

#define DEF_HTABLE_OA(tname, K, V)\
DEF_HTABLE_OA_STRUCT(tname, K, V)\
DEF_HTABLE_OA_IS_ALLOCATED(tname, K, V)\
DEF_HTABLE_OA_SET_ALLOCATED(tname, K, V)\
DEF_HTABLE_OA_CONSTRUCTOR(tname, K, V)\
DEF_HTABLE_OA_DESTRUCTOR(tname, K, V)\
DEF_HTABLE_OA_INSERT(tname, K, V)\
DEF_HTABLE_OA_FIND(tname, K, V)\
DEF_HTABLE_OA_DELETE(tname, K, V)\
DEF_HTABLE_OA_REBUILD(tname, K, V)

#endif

