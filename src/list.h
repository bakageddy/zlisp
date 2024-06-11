#ifndef ZLISP_LIST_H
#define ZLISP_LIST_H

#ifndef ZLISP_LIST_INITIAL_CAPACITY
#define ZLISP_LIST_INITIAL_CAPACITY 16
#endif // ZLISP_LIST_INITIAL_CAPACITY

#include <stddef.h>

typedef struct {
	void **data;
	size_t cap;
	size_t len;
} zlisp_list_t;

typedef void (*zlisp_element_printer_t)(void *elem);

zlisp_list_t *create_list(void);
int list_append(zlisp_list_t *list, void *elem);
void list_print(zlisp_list_t *list, zlisp_element_printer_t f);
void *list_pop(zlisp_list_t *list);
void delete_list(zlisp_list_t *list);

#ifdef ZLISP_LIST_IMPL

#include <stdlib.h>
#include "../src/utils.h"

zlisp_list_t *create_list(void) {
	zlisp_list_t *list = calloc(1, sizeof(*list));
	if (list == NULL) {
		return NULL;
	}

	void *data = calloc(ZLISP_LIST_INITIAL_CAPACITY, sizeof(void*));
	if (data == NULL) {
		free(list);
		return NULL;
	} 
	list -> data = data;
	list -> cap = 16;
	list -> len = 0;
	return list;
}

int expand_list(zlisp_list_t *list) {
	if (list == NULL) return -1;
	void *buf = realloc(list -> data, sizeof(void*) * list -> cap * 2);
	if (buf == NULL) {
		ERR("Failed to expand list!\n");
		return -1;
	}
	list -> data = buf;
	list -> cap *= 2;
	return 0;
}

int shrink_list(zlisp_list_t *list) {
	if (list == NULL) return -1;;
	void *buf = realloc(list -> data, sizeof(void*) * (int) (list -> cap * 0.5));
	if (buf == NULL) {
		ERR("Failed to shrink list!");
		return -1;
	}
	list -> data = buf;
	list -> cap *= 2;
	return 0;
}

int list_append(zlisp_list_t *list, void *elem) {
	if (list == NULL || elem == NULL)  return -1;
	if (list -> len == list -> cap && expand_list(list) < 0) {
		return -1;
	}

	list -> data[list -> len] = elem;
	list -> len += 1;
	return 0;
}

void *list_pop(zlisp_list_t *list) {
	if (list == NULL) return NULL;
	if (list -> len == 0) return NULL;
	if (list -> len == (size_t) (list -> cap * 0.5) && shrink_list(list) < 0) {
		return NULL;
	}
	void *elem = list -> data[list -> len];
	list -> len -= 1;
	return elem;
}

void list_print(zlisp_list_t *list, zlisp_element_printer_t f) {
	for (size_t i = 0; i < list -> len; i++) {
		f(list -> data[i]);
	}
}

void delete_list(zlisp_list_t *list) {
	if (list == NULL) return;
	free(list -> data);
	free(list);
}

#endif // ZLISP_LIST_IMPL
#endif // ZLISP_LIST_H
