#ifndef ZLISP_STRING_H
#define ZLISP_STRING_H

#include <stdint.h>
#include "allocator.h"

typedef struct {
	char *data;
	uint64_t len;
	uint64_t capacity;
} zlisp_string_t;

typedef struct {
	char *data;
	uint64_t len;
} zlisp_string_view_t;

zlisp_string_t zlisp_string_init(zlisp_allocator_t allocator, uint64_t capacity);
zlisp_string_view_t zlisp_string_view(zlisp_string_t string); 
zlisp_string_view_t zlisp_string_view_static(const char *data);
void zlisp_string_destroy(zlisp_allocator_t allocator, zlisp_string_t string);

#endif // ZLISP_STRING_H
