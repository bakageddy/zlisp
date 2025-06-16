#ifndef ZLISP_LIST_H
#define ZLISP_LIST_H

#include "arena.h"

typedef struct zlisp_node_t {
	void *data;
	struct zlisp_node_t *next;
	struct zlisp_node_t *prev;
} zlisp_node_t;

typedef struct {
	zlisp_node_t *head;
	zlisp_node_t *tail;
} zlisp_list_t;

zlisp_list_t zlisp_list_init();
void zlisp_destroy(zlisp_list_t list);

#endif // ZLISP_ARENA_H
