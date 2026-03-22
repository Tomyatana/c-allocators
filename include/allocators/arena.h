#ifndef _ARENA_H
#define _ARENA_H

#include <inttypes.h>
#include <stdlib.h>

#define ALIGN(v, a) (((v) + ((a) - 1)) & ~((a) - 1))

#define ARENA_CHUNK_SIZE 4096

struct arena {
	struct arena_chunk* chunks;
};

struct arena_chunk;

void* arena_alloc_align(struct arena *a, size_t s, size_t align);
void arena_reset(struct arena *a);
void arena_init(struct arena* a);

#define arena_alloc(a, s) arena_alloc_align((a), (s), _Alignof(void*))

#endif
