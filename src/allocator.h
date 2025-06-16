#ifndef ZLISP_ALLOCATOR_H
#define ZLISP_ALLOCATOR_H

#include <stdint.h>

typedef void* (*zlisp_allocator_f)(void *state, uint64_t capacity);
typedef void (*zlisp_deallocator_f)(void *state, void *data);
typedef void* (*zlisp_reallocator_f)(void *state, void *data, uint64_t new_capacity);

typedef void* (*zlisp_init_f)(void *state);
typedef void (*zlisp_destroy_f)(void *state);

typedef struct {
	zlisp_allocator_f allocator;
	zlisp_deallocator_f deallocator;
	zlisp_reallocator_f reallocator;
	zlisp_init_f init;
	zlisp_destroy_f destroy;
	void *state;
} zlisp_allocator_t;

#endif
