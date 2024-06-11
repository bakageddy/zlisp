#include <stddef.h>
#include <stdio.h>

#define ZLISP_LEXER_IMPL
#include "src/lexer.h"

#define ZLISP_LIST_IMPL
#include "src/list.h"

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
		exit(1);
	}

	printf("File Name: %s\n", lexer -> file_name);
	printf("Contents:\n%.*s", (int) lexer -> file_size, lexer -> file_contents);

	zlisp_list_t *list = create_list();
	if (list == NULL) {
		ERR("Failed to create token list!");
		goto defer;
	}

	token_t *tok;
	do {
		tok = next_token(lexer);
		if (tok == NULL) {
			ERR("Failed to get token!");
			goto defer;
		}
		if (list_append(list, tok) < 0) {
			ERR("Failed to append token!");
			goto defer;
		}
	} while (tok -> type != UNINITIALIZED);
	list_print(list, (zlisp_element_printer_t) print_token);

defer:
	for (size_t i = 0; i < list -> len; i++) {
		free_token(list -> data[i]);
	}
	delete_list(list);
	delete_lexer(lexer);
	return 0;
}
