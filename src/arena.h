#ifndef ZLISP_ARENA_H
#define ZLISP_ARENA_H

#include <stdint.h>

typedef struct {
	void *data;
	uint64_t capacity;
	uint64_t len;
} zlisp_arena_t;

zlisp_arena_t zlisp_arena_init(uint64_t capacity);
void *zlisp_arena_allocate(zlisp_arena_t arena, uint64_t block_size);
void zlisp_arena_destory(zlisp_arena_t arena);

#endif // ZLISP_ARENA_H
