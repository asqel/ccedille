#ifndef TOKENS_H
#define TOKENS_H

#include "types.h"
#include <stdlib.h>

typedef struct {
	u8 type;
	union {
		char *str;
		char *id;
		u8 c;
		u16 w;
		u32 dw;
		u64 l;
		u32 syntax;
	} val;
	int line;
} token_t;

enum TOKEN_TYPES {
	TOKEN_NONE_T,
	TOKEN_STR_T,
	TOKEN_IDENTIFIER_T,
	TOKEN_CHAR_T,
	TOKEN_WORD_T,
	TOKEN_DWORD_T,
	TOKEN_LONG_T,
	TOKEN_SYNTAX_T
};

char *tokens_syntax[] = {"#", "@", ",", "?", ":", "(", ")", "[", "]", "{", "}", NULL};
char *tokens_op1[] = {"+", "-", "/", "*", "=", "<", ">", "!", "&", "|", "~", "^", "%", ".", NULL};
char *tokens_op2[] = {"+=", "-=", "*=", "/=", "&=", "|=", "^=", "%=", "~~", "==", "!=", "<=", ">=", "++", "--", "->", ">>", "<<", NULL};
char *tokens_op3[] = {"~~=",  "<<=", ">>=", NULL};

typedef struct {
	token_t *tokens;
	uint len;
} token_list_t;

void token_list_append(token_list_t *lst, token_t tok);
token_list_t *new_token_list();

#endif