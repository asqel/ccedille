#include  "tokens.h"


int main() {
	token_list_t *tokens = lexe("\"salut\" <<=");
	for (int i = 0; i < tokens->len; i++) {
		token_print(tokens->tokens[i]);
	}
	return 0;
}