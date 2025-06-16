#include <stdlib.h>
#include "arena.h"

zlisp_arena_t zlisp_arena_init(uint64_t capacity) {
	zlisp_arena_t arena;
	arena.data = malloc(capacity);
	if (arena.data == NULL) {
		arena.capacity = 0;
		arena.len = 0;
		return arena;
	}

	arena.capacity = capacity;
	arena.len = 0;
	return arena;
}

void *zlisp_arena_allocate(zlisp_arena_t arena, uint64_t block_size) {
	if (arena.capacity == 0 || arena.data == NULL) return NULL;
	if (arena.len + block_size >= arena.capacity) return NULL;

	void *allocated = arena.data + arena.len;
	arena.len += block_size;
	return allocated;
}

void zlisp_arena_destory(zlisp_arena_t arena) {
	if (arena.capacity == 0 || arena.len == 0) return;
	free(arena.data);
	arena.data = NULL;
	arena.capacity = 0;
	arena.len = 0;
	return;
}
