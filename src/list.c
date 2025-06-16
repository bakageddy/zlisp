#include <stdlib.h>
#include "list.h"
#include "error.h"

zlisp_list_t zlisp_list_init() {
	return (zlisp_list_t) {
		.head = NULL,
		.tail = NULL
	};
}

zlisp_error_t zlisp_list_push(zlisp_list_t list, zlisp_node_t *node) {
	if (list.head == NULL || list.tail == NULL) {
		list.head = node;
		list.tail = node;
	}
	return (zlisp_error_t) {
		.kind = OK,
		.string = {}
	};
}
