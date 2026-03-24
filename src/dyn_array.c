#include "allocators/dyn_array.h"

inline void* da_pop(void* da) {
	if (da_len(da) != 0)
		return da + da_header(da)->len--;
	return NULL;
}
