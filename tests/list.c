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

	token_t *tok = next_token(lexer);
	if (tok == NULL) return 0;
	list_append(list, tok);

	assert((token_t*) list -> data[0] == tok);

	delete_lexer(lexer);
	delete_list(list);
	return 0;
}
