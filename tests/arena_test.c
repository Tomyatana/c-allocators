#include "allocators/arena.h"
#include "unity.h"

void setUp() {}

void tearDown() {}

void test_arena_align() {
	struct arena arena;
	arena_init(&arena);
	int* ints = arena_alloc_align(&arena, 16, _Alignof(int));
	int* ints2 = arena_alloc_align(&arena, 16, _Alignof(int));
	TEST_ASSERT_NOT_EQUAL_HEX64(NULL, &arena);

	for (size_t i = 0; i < 16/sizeof(int); i++) {
		ints[i] = i;
		ints2[i] = i*2;
	}

	for (size_t i = 0; i < 16/sizeof(int); i++) {
		TEST_ASSERT_EQUAL_INT(i, ints[i]);
		TEST_ASSERT_EQUAL_INT(i*2, ints2[i]);
	}

	arena_reset(&arena);
	TEST_ASSERT_EQUAL_HEX64(NULL, arena.chunks);
}

void test_arena_alloc() {
	struct arena arena;
	arena_init(&arena);
	int* ints = arena_alloc(&arena, 16);
	int* ints2 = arena_alloc(&arena, 16);
	TEST_ASSERT_NOT_EQUAL_HEX64(NULL, &arena);

	for (size_t i = 0; i < 16/sizeof(int); i++) {
		ints[i] = i;
		ints2[i] = i*2;
	}

	for (size_t i = 0; i < 16/sizeof(int); i++) {
		TEST_ASSERT_EQUAL_INT(i, ints[i]);
		TEST_ASSERT_EQUAL_INT(i*2, ints2[i]);
	}

	arena_reset(&arena);
	TEST_ASSERT_EQUAL_HEX64(NULL, arena.chunks);
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_arena_align);
	RUN_TEST(test_arena_alloc);
	return UNITY_END();
}
