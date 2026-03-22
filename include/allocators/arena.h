#ifndef _ARENA_H
#define _ARENA_H

#include <inttypes.h>
#include <stdlib.h>

#define ALIGN(v, a) (((v) + (a)) & -(a))

#define ARENA_CHUNK_SIZE 1048

struct arena {
	struct arena_chunk* chunks;
};

struct arena_chunk;

#endif
