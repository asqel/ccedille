#include <stdlib.h>

#include "tokens.h"

void token_list_append(token_list_t *lst, token_t tok) {
	lst->len++;
	lst->tokens = realloc(lst->tokens, sizeof(token_t) * lst->len);
	lst->tokens[lst->len - 1] = tok;
}

token_list_t *new_token_list() {
	token_list_t *res = malloc(sizeof(token_list_t));
	if (res == NULL)
		return res;
	res->len = 0;
	res->tokens = NULL;
	return res;
}