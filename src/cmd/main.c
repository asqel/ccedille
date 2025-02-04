#include "tokens.h"

#include <stdio.h>
static int main_test() {
	FILE *file = fopen("test/test.cdy", "r");
	if (file == NULL) {
		printf("Error: file not found\n");
		return 1;
	}
	int len = 0;
	fseek(file, 0, SEEK_END);
	len = ftell(file);
	fseek(file, 0, SEEK_SET);
	char *text = malloc(len + 1);
	fread(text, 1, len, file);
	text[len] = '\0';
	fclose(file);
	token_list_t *tokens = lexe(text);
	extern int last_error;
	printf("ptr = %p %d\n", tokens, last_error);
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