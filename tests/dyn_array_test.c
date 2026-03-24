#include "allocators/dyn_array.h"
#include "unity.h"

void setUp() {}

void tearDown() {}

void test_dyn_array_init() {
	int* arr;

	da_init(arr);

	TEST_ASSERT_EQUAL(da_cap(arr), 256);
	TEST_ASSERT_EQUAL(da_len(arr), 0);

	da_deinit(arr);
}

void test_dyn_array_push() {
	int* arr;

	da_init(arr);

	TEST_ASSERT_EQUAL(da_cap(arr), 256);
	TEST_ASSERT_EQUAL(da_len(arr), 0);

	for (size_t i = 0; i < 10; i++) {
		da_push(arr, i);
	}

	for (size_t i = 0; i < da_len(arr); i++) {
		TEST_ASSERT_EQUAL(arr[i], i);
	}


	da_deinit(arr);
}

void test_dyn_array_push_init() {
	int* arr = NULL;

	da_push(arr, 0);

	TEST_ASSERT_EQUAL(da_cap(arr), 256);
	TEST_ASSERT_EQUAL(da_len(arr), 1);

	for (size_t i = 1; i < 10; i++) {
		da_push(arr, i);
	}

	for (size_t i = 0; i < da_len(arr); i++) {
		TEST_ASSERT_EQUAL(arr[i], i);
	}


	da_deinit(arr);
}

void test_dyn_array_realloc() {
	int* arr = NULL;

	da_push(arr, 0);

	TEST_ASSERT_EQUAL(da_cap(arr), 256);
	TEST_ASSERT_EQUAL(da_len(arr), 1);

	for (size_t i = 1; i < 512; i++) {
		da_push(arr, i);
	}

	for (size_t i = 0; i < da_len(arr); i++) {
		TEST_ASSERT_EQUAL(i, arr[i]);
	}


	da_deinit(arr);
}

void test_dyn_array_pop() {
	int* arr = NULL;

	da_push(arr, 0);

	TEST_ASSERT_EQUAL(da_cap(arr), 256);
	TEST_ASSERT_EQUAL(da_len(arr), 1);

	for (size_t i = 1; i < 10; i++) {
		da_push(arr, i);
	}

	TEST_ASSERT_EQUAL(9, da_len(arr));

	da_pop(arr);
	

	da_deinit(arr);
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_dyn_array_init);
	RUN_TEST(test_dyn_array_push);
	RUN_TEST(test_dyn_array_push_init);
	RUN_TEST(test_dyn_array_realloc);
	return UNITY_END();
}
