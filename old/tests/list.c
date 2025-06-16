#include <assert.h>

#define ZLISP_LIST_IMPL
#include "../src/list.h"

#define ZLISP_LEXER_IMPL
#include "../src/lexer.h"

int main(int argc, char **argv) {
	zlisp_list_t *list = create_list();
	if (list == NULL) return 0;
	zlisp_lexer_t *lexer = init_lexer("../main.zl");
	if (lexer == NULL) {
		delete_list(list);
		return 0;
	}

	for (int i = 0;; i++) {
		token_t *tok = next_token(lexer);
		if (tok->type == UNINITIALIZED) break;
		list_append(list, tok);
		print_token(list -> data[i]);
	}

	delete_lexer(lexer);
	delete_list(list);
	return 0;
}
