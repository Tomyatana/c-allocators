#include "allocators/arena.h"

struct arena_chunk {
	struct arena_chunk* next;
	uint8_t* end;
	uint8_t* head;
	uint8_t buffer[];
};

void arena_chunk_init(struct arena_chunk* ck, struct arena_chunk* next) {
	ck->next = next;
	ck->end = ((uint8_t*)ck) + ARENA_CHUNK_SIZE;
	ck->head = ck->buffer;
}

#ifndef __linux
struct arena_chunk* arena_chunk_new(struct arena* a) {
	struct arena_chunk* ck = malloc(ARENA_CHUNK_SIZE);
	if (!ck) {
		return NULL;
	}

	arena_chunk_init(ck, a->chunks);
	a->chunks = ck;

	return ck;
}

#else

#include <sys/mman.h>

struct arena_chunk* arena_chunk_new(struct arena* a) {
	struct arena_chunk* ck = mmap(NULL, ARENA_CHUNK_SIZE, PROT_READ | PROT_WRITE,
							   MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (ck == MAP_FAILED) {
		return NULL;
	}

	arena_chunk_init(ck, a->chunks);
	a->chunks = ck;

	return ck;
}
#endif

void* arena_chunk_alloc(struct arena_chunk* ck, size_t s, size_t align) {
	uint8_t* head = (uint8_t*)ALIGN((uintptr_t)ck->head, align);

	if (head + s > ck->end) {
		return NULL;
	}

	ck->head = head + s;

	return head;
}

struct arena_chunk* arena_get_chunk(struct arena* a) {
	if (a->chunks)
		return a->chunks;

	return arena_chunk_new(a);
}

void* arena_alloc_align(struct arena* a, size_t s, size_t align) {
	struct arena_chunk* ck = arena_get_chunk(a);
	if (!ck)
		return NULL;

	void* buf = arena_chunk_alloc(ck, s, align);
	if (buf)
		return buf;

	ck = arena_chunk_new(a);
	return arena_chunk_alloc(ck, s, align);
}

#ifndef __linux
void arena_reset(struct arena* a) {
	struct arena_chunk* ck = a->chunks;

	while (ck) {
		struct arena_chunk* next = ck->next;
		free(ck);
		ck = next;
	}

	a->chunks = NULL;
}
#else

void arena_reset(struct arena* a) {
	struct arena_chunk* ck = a->chunks;

	while (ck) {
		struct arena_chunk* next = ck->next;
		munmap(ck, ARENA_CHUNK_SIZE);
		ck = next;
	}

	a->chunks = NULL;
}

#endif

void arena_init(struct arena* a) {
	a->chunks = NULL;
	arena_chunk_new(a);
}
