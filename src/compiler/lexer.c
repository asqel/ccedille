#include "compiler/tokens.h"
#include <stdlib.h>
#include <string.h>
#include <string.h>

static int is_lexer_skip(char c) {
	if (c == '\r' || c == '\v'  || c == '\t')
		return 1;
	if (c == ' ' || c == '\f')
		return 1;
	return 0;
}

_Noreturn static void do_error(lexer_ctx_t *ctx, int err) {
	ctx->error  = err;
	longjmp(ctx->jmp_buffer, 1);
}

void lexe(lexer_ctx_t *ctx, char *text) {
	size_t idx = 0;
	int line = 1;

	while (text[idx] != '\0') {
		if (text[idx] == '\n') {
			line++;
			idx++;
			continue;
		}
		if (is_lexer_skip(text[idx])) {
			idx++;
			continue;
		}
		if (text[idx] == '/' && text[idx + 1] == '/') {
			idx += 2;
			while (text[idx] != '\n' && text[idx] != '\0')
				idx++;
			continue;
		}
		if (text[idx] == '/' && text[idx + 1] == '*') {
			idx += 2;
			while (text[idx] != '\0') {
				if (text[idx] == '\n')
					line++;
				if (text[idx] == '*' && text[idx + 1] == '/')
					break;
				idx++;
			}
			if (text[idx] == '\0')
				do_error(ctx, 1);
			idx += 2;
			continue;
		}
	}
}