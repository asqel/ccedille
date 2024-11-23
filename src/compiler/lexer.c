#include "tokens.h"
#include <stdlib.h>
#include <string.h>

static int is_lexer_skip(char c) {
	if (c == '\r' || c == '\v'  || c == '\t')
		return 1;
	if (c == ' ' || c == '\f')
		return 1;
	return 0;
}

static int get_syntax_token_type(char *c) {
	int p = 0;
	while (tokens_syntax[p] != NULL) {
		if (!strncmp(tokens_syntax[p], c, strlen(tokens_syntax[p])))
			return p;
	}
	return -1;
}



token_list_t *lexe(char *text) {
	uint idx = 0;
	int line = 1;
	token_list_t *res = new_token_list();
	if (res == NULL)
		return NULL;
	while (text[idx] != '\0') {
		if (text[idx] == '\n') {
			line++;
			idx++;
		}
		else if (is_lexer_skip(text[idx]))
			idx++;
		else if (text[idx]) {

		}
	}
	return res;
}