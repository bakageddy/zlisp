#ifndef ZLISP_PARSER_H
#define ZLISP_PARSER_H

#include "lexer.h"

typedef struct {
	zlisp_lexer_t *lexer;
} zlisp_parser_t;

typedef enum {
	PARSER_FN,
	PARSER_EXPRESSION,
} node_type;

typedef struct {} parser_fn_node_t;
typedef struct {} parser_expr_node_t;

typedef union {
	parser_fn_node_t *fn;
	parser_expr_node_t *expr;
} node_t;

typedef struct {
	node_type type;
	node_t node;
} parser_node_t;

#endif // !ZLISP_PARSER_H
