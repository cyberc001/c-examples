#include <stdlib.h>

#define DEF_LLIST_STRUCT(tname, T)\
typedef struct llist_node_ ## tname llist_node_ ## tname;\
struct llist_node_ ## tname{\
	struct llist_node_ ## tname * next;\
	T data;\
};\
\
typedef struct{\
	llist_node_ ## tname * first;\
} llist_ ## tname;


#define DEF_LLIST_NEW(tname, T)\
void llist_ ## tname ## _new(llist_ ## tname* self)\
{\
	self->first = NULL;\
}

#define DEF_LLIST_INSERT_END(tname, T)\
void llist_ ## tname ## _insert_end(llist_ ## tname* self, T el)\
{\
	if(!self->first){\
		self->first = malloc(sizeof(llist_node_ ## tname));\
		self->first->next = NULL;\
		self->first->data = el;\
		return;\
	}\
	llist_node_ ## tname* it = self->first;\
	while(it->next) it = it->next;\
	it->next = malloc(sizeof(llist_node_ ## tname));\
	it->next->next = NULL;\
	it->next->data = el;\
}

#define DEF_LLIST_ITERATE(tname, T)\
void llist_ ## tname ## _iterate(llist_ ## tname* self, void (*it_func)(T el))\
{\
	if(!self->first)\
		return;\
	llist_node_ ## tname* it = self->first;\
	while(it){\
		it_func(it->data);\
		it = it->next;\
	}\
}

#define DEF_LLIST_DELETE(tname, T)\
void llist_ ## tname ## _delete(llist_ ## tname* self)\
{\
	if(!self->first)\
		return;\
	llist_node_ ## tname* it = self->first;\
	while(it){\
		llist_node_ ## tname* next = it->next;\
		free(it);\
		it = next;\
	}\
}


#define DEF_LLIST(tname, T)\
DEF_LLIST_STRUCT(tname, T)\
DEF_LLIST_NEW(tname, T)\
DEF_LLIST_INSERT_END(tname, T)\
DEF_LLIST_ITERATE(tname, T)\
DEF_LLIST_DELETE(tname, T)
