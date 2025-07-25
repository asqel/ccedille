#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "compiler/tokens.h"


char *tokens_syntax[] = {"#", "@", ",", "?", ":", "(", ")", "[", "]", "{", "}", ";", NULL};
char *tokens_op1[] = {"+", "-", "/", "*", "=", "<", ">", "!", "&", "|", "~", "^", "%", ".", NULL};
char *tokens_op2[] = {"+=", "-=", "*=", "/=", "&=", "|=", "^=", "%=", "~~", "==", "!=", "<=", ">=", "++", "--", "->", ">>", "<<", NULL};
char *tokens_op3[] = {"~~=",  "<<=", ">>=", NULL};

void token_list_append(token_list_t *lst, token_t tok) {
	lst->tokens = realloc(lst->tokens, sizeof(token_t) * (lst->len + 1));
	lst->tokens[lst->len] = tok;
	lst->len++;
}

token_list_t *new_token_list() {
	token_list_t *res = malloc(sizeof(token_list_t));
	if (res == NULL)
		return res;
	res->len = 0;
	res->tokens = NULL;
	return res;
}

void token_free(token_t tok) {
	switch (tok.type) {
		case TOKEN_STR_T:
			free(tok.val.str);
			break;
		case TOKEN_IDENTIFIER_T:
			free(tok.val.id);
			break;
	}
}

void token_list_free(token_list_t *lst) {
	for (int i = 0; i < lst->len; i++) {
		token_free(lst->tokens[i]);
	}
	free(lst->tokens);
	free(lst);
}

u32 token_op_str_to_enum(char *str) {
	for (int i = 0; i < tokens_op3_len; i++) {
		if (!strncmp(tokens_op3[i], str, 3))
			return i + tokens_op1_len + tokens_op2_len;
	}
	for (int i = 0; i < tokens_op2_len; i++) {
		if (!strncmp(tokens_op2[i], str, 2))
			return i + tokens_op1_len;
	}
	for (int i = 0; i < tokens_op1_len; i++) {
		if (!strncmp(tokens_op1[i], str, 1))
			return i;
	}
	return TOKEN_OP_NONE_T;
}


void token_print(token_t tok) {
	switch (tok.type) {
		case TOKEN_STR_T:
			printf("T_STR[%s]", tok.val.str);
			break;
		case TOKEN_IDENTIFIER_T:
			printf("T_ID[%s]", tok.val.id);
			break;
		case TOKEN_OPERATOR_T:
			if (tok.val.op < tokens_op1_len)
				printf("T_OP1[%s]", tokens_op1[tok.val.op]);
			else if (tok.val.op < tokens_op1_len + tokens_op2_len)
				printf("T_OP2[%s]", tokens_op2[tok.val.op - tokens_op1_len]);
			else if (tok.val.op < tokens_op1_len + tokens_op2_len + tokens_op3_len)
				printf("T_OP3[%s]", tokens_op3[tok.val.op - tokens_op1_len - tokens_op2_len]);
			else
				printf("T_OP_[NONE]");
			break;
		case TOKEN_SYNTAX_T:
			printf("T_SYNTAX['%s']", tokens_syntax[tok.val.syntax]);
			break;
		case TOKEN_INT_T:
			printf("T_DWORD[%d]", tok.val.i);
			break;
		default:
			printf("T_[%d]", tok.type);
	}
}