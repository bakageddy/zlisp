#ifndef ZLISP_TOKEN_H
#define ZLISP_TOKEN_H

#include <stddef.h>

typedef enum {
	UNINITIALIZED = 0,
	LPAREN,
	RPAREN,
	ATOM,
	TYPE,
	IDENT,
	STRING_LITERAL,
	LITERAL,
	KEYWORD_FN,
} token_type_t;

typedef struct {
	token_type_t type;
	// ONLY for IDENT, STRING_LITERAL, ATOM, TYPE
	char *buf;
	size_t n;
} token_t;

token_t *new_token(token_type_t type);
int token_append(token_t *tok, char c);
void free_token(token_t *tok);
void print_token(token_t *tok);

#ifdef ZLISP_TOKEN_IMPL
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "utils.h"

char* token_names[] = {
	[UNINITIALIZED] = "UNINITIALIZED",
	[LPAREN] = "LPAREN",
	[RPAREN] = "RPAREN",
	[ATOM] = "ATOM",
	[TYPE] = "TYPE",
	[IDENT] = "IDENT",
	[STRING_LITERAL] = "STRING_LITERAL",
	[LITERAL] = "LITERAL",
	[KEYWORD_FN] = "KEYWORD_FN",
};

inline void print_token(token_t *tok) {
	assert(tok != NULL);
	printf("TOKEN TYPE: %s\t\tTOKEN: %.*s\n", token_names[tok -> type], (int) tok -> n, tok -> buf);
}

// TODO: Analyze if owning tokens or borrowing tokens is useful
token_t *new_token(token_type_t type) {
	token_t *tok = calloc(1, sizeof(*tok));
	if (tok == NULL) return NULL;
	tok -> type = type;
	tok -> buf = NULL;
	tok -> n = 0;
	return tok;
}

int token_append(token_t *tok, char c) {
	assert(tok != NULL);
	// TODO: Implement tokens in a separate string library
	
	char *buf = realloc(tok -> buf, sizeof(char) * (tok -> n + 1));
	if (buf == NULL) {
		ERR("Failed to expand token!");
		return -1;
	}
	tok -> buf = buf;
	tok -> buf[tok -> n] = c;
	tok -> n += 1;
	return 0;
}

void free_token(token_t *tok) {
	free(tok -> buf);
	free(tok);
}

#endif // ZLISP_TOKEN_IMPL
#endif // ZLISP_TOKEN_H
