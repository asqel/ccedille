#include "compiler/tokens.h"
#include "utils.h"
#include <stdio.h>

static int main_test() {
	char *text = uti_read_file("test/test.cdy");

	token_list_t *tokens = lexe(text);
	extern int last_error;
	printf("ptr =      %p %d\n", tokens, last_error);
	printf("len = %d\n", tokens->len);
	for (int i = 0; i < tokens->len; i++) {
		token_print(tokens->tokens[i]);
		if (i < tokens->len - 1 && tokens->tokens[i].line != tokens->tokens[i + 1].line) {
			printf("\n");
		}
		else
			printf(" ");
	}
	printf("\n");
	token_list_free(tokens);
	free(text);
	return 0;
}

int main() {
	main_test();
	return 0;
}