#define ZLISP_LEXER_IMPL
#include "src/lexer.h"

#define ZLISP_TOKEN_IMPL
#include "src/token.h"

#include "src/utils.h"
#include <stdio.h>

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("USAGE: zlisp [FILENAME]\n");
		return 1;
	}

	zlisp_lexer_t *lexer = init_lexer(argv[1]);
	if (lexer == NULL) {
		ERR("Failed to initialize lexer!");
		return 1;
	}

	printf("File Name: %s\n", lexer -> file_name);
	printf("Contents: %.*s", (int) lexer -> file_size, lexer -> file_contents);
	while (has_content(lexer)) {
		token_t token = next_token(lexer);
		print_token(&token);
		free_token(&token);
	}
	delete_lexer(lexer);
	return 0;
}
