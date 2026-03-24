#ifndef _DYN_ARRAY_H
#define _DYN_ARRAY_H

#include <stddef.h>
#include <stdlib.h>

#define DA_INITIAL_CAPACITY 256
#define DA_GROW_RATE 2

struct dyn_array_header {
	size_t cap;
	size_t len;
};

#define da_header(da) (((struct dyn_array_header*) (da)) - 1)
#define da_len(da) da_header((da))->len
#define da_cap(da) da_header((da))->cap

#define da_init(da)\
	do {\
		(da) = malloc(sizeof(struct dyn_array_header) + DA_INITIAL_CAPACITY * sizeof (*da)) + sizeof(struct dyn_array_header);\
		da_header(da)->cap = DA_INITIAL_CAPACITY;\
		da_header(da)->len = 0;\
	} while(0)

#define da_push(da, e)\
	do {\
		if (!(da)) da_init(da);\
		if (da_len(da) + 1 >= da_cap(da)) {\
			(da) = (void*)(char*)realloc(da_header(da), da_cap(da) * sizeof(*(da)) * DA_GROW_RATE + sizeof(struct dyn_array_header)) + sizeof (struct dyn_array_header);\
			da_header(da)->cap *= DA_GROW_RATE;\
		}\
		da[da_header(da)->len++] = e;\
	} while(0)

#define da_deinit(da)\
	do {\
		free(da_header(da));\
		da = NULL;\
	} while(0)

void* da_pop(void* da);

#endif
