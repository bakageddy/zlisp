#ifndef ZLISP_LEXER_H
#define ZLISP_LEXER_H

#include <stddef.h>

#define ZLISP_TOKEN_IMPL
#include "token.h"

typedef struct {
	char *file_name;
	char *file_contents;
	size_t file_size;
	size_t cursor;
	char curr;
} zlisp_lexer_t;

zlisp_lexer_t *init_lexer(char *file_name);
token_t *next_token(zlisp_lexer_t *l);
void delete_lexer(zlisp_lexer_t *lexer);

#ifdef ZLISP_LEXER_IMPL

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>


#include "utils.h"

zlisp_lexer_t *init_lexer(char *file_name) {
	assert(file_name != NULL);
	zlisp_lexer_t *lexer = NULL;
	int handle = open(file_name, O_RDONLY);
	if (handle < 0) {
		ERR("Failed to open file: %s", file_name);
		return NULL;
	}

	struct stat st;
	if (fstat(handle, &st) < 0) {
		ERR("Failed to stat file: %s", file_name);
		return NULL;
	}

	size_t size = st.st_size;
	char *file_buf = calloc(size, sizeof(char));
	if (file_buf == NULL) {
		ERR("OUT OF MEMORY!");
		return NULL;
	}

	if (read(handle, file_buf, size) < 0) {
		ERR("Failed to map file!");
		free(file_buf);
		return NULL;
	}

	lexer = calloc(1, sizeof(*lexer));
	if (lexer == NULL) {
		ERR("Failed to map lexer to memory!");
		free(file_buf);
		return NULL;
	}

	lexer -> file_name = file_name;
	lexer -> file_contents = file_buf;
	lexer -> file_size = size;
	lexer -> cursor = 0;
	// TODO: Handle case when file_size == 0
	lexer -> curr = lexer -> file_contents[lexer -> cursor];
	close(handle);

	return lexer;
}

bool has_content(zlisp_lexer_t *l) {
	return (l -> file_size > l -> cursor);
}

bool is_whitespace(char c) {
	return c == '\n' || c == '\r' || c == '\t' || c == ' ';
}

bool is_reserved(char c) {
	return c == ')' || c == '(' || c == ':';
}

void consume(zlisp_lexer_t *l) {
	assert(has_content(l) == true);
	l -> cursor += 1;
	l -> curr = l -> file_contents[l -> cursor];
}

void consume_whitespace(zlisp_lexer_t *l) {
	while (has_content(l) && is_whitespace(l -> curr)) {
		consume(l);
	}
}

token_t *next_token(zlisp_lexer_t *l) {
	consume_whitespace(l);
	if (l -> curr == '(') {
		token_t *tok = new_token(LPAREN);
		if (tok == NULL) return NULL;
		consume(l);
		return tok;
	} else if (l -> curr == ')') {
		token_t *tok = new_token(RPAREN);
		if (tok == NULL) return NULL;
		consume(l);
		return tok;
	} else if (l -> curr == ':') {
		token_t *tok = new_token(ATOM);
		if (tok == NULL) return NULL;
		do {
			token_append(tok, l -> curr);
			consume(l);
		} while (has_content(l) && !is_whitespace(l -> curr) && !is_reserved(l -> curr));
		return tok;
	} else if (isalpha(l -> curr)) {
		token_t *tok = new_token(IDENT);
		if (tok == NULL) return NULL;
		do {
			token_append(tok, l -> curr);
			consume(l);
		} while (has_content(l) && !is_whitespace(l -> curr) && !is_reserved(l -> curr));
		return tok;
	} else if (isdigit(l -> curr)) {
		token_t *tok = new_token(LITERAL);
		if (tok == NULL) return NULL;
		do {
			token_append(tok, l -> curr);
			consume(l);
		} while (has_content(l) && isdigit(l -> curr) && !is_whitespace(l -> curr));
		return tok;
	} else if (l -> curr == '"') {
		token_t *tok = new_token(STRING_LITERAL);
		if (tok == NULL) return NULL;
		consume(l);
		do {
			token_append(tok, l -> curr);
			consume(l);
		} while (has_content(l) && l -> curr != '"');
		consume(l);
		return tok;
	} else {
		token_t *tok = new_token(UNINITIALIZED);
		return tok;
	}
}

void delete_lexer(zlisp_lexer_t *lexer) {
	free(lexer -> file_contents);
	free(lexer);
}

#endif // ZLISP_LEXER_IMPL

#endif // ZLISP_LEXER_H
