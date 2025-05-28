#ifndef TOKENS_H
#define TOKENS_H

#include "types.h"
#include <stdlib.h>

typedef struct {
	u8 type;
	union {
		char *str;
		char *id;
		i64 i;
		double f;
		u32 op;
		u32 syntax;
		u32 keyword;
	} val;
	int line;
} token_t;

typedef struct {
	token_t *tokens;
	uint len;
} token_list_t;


enum TOKEN_TYPES {
	TOKEN_NONE_T,
	TOKEN_STR_T,
	TOKEN_IDENTIFIER_T,
	TOKEN_CHAR_T,
	TOKEN_WORD_T,
	TOKEN_INT_T,
	TOKEN_LONG_T,
	TOKEN_SYNTAX_T,
	TOKEN_OPERATOR_T
};

extern char *tokens_syntax[];
extern char *tokens_op1[];
extern char *tokens_op2[];
extern char *tokens_op3[];
#define tokens_op1_len 14
#define tokens_op2_len 18
#define tokens_op3_len 3

enum {
	TOKEN_OP_PLUS_T,
	TOKEN_OP_MINUS_T,
	TOKEN_OP_DIV_T,
	TOKEN_OP_MUL_T,
	TOKEN_OP_ASSIGN_T,
	TOKEN_OP_LESS_T,
	TOKEN_OP_GREATER_T,
	TOKEN_OP_NOT_T,
	TOKEN_OP_BIT_AND_T,
	TOKEN_OP_BIT_OR_T,
	TOKEN_OP_BIT_NOT_T,
	TOKEN_OP_BIT_XOR_T,
	TOKEN_OP_MOD_T,
	TOKEN_OP_DOT_T,
	TOKEN_OP_PLUS_ASSIGN_T,
	TOKEN_OP_MINUS_ASSIGN_T,
	TOKEN_OP_MUL_ASSIGN_T,
	TOKEN_OP_DIV_ASSIGN_T,
	TOKEN_OP_BIT_AND_ASSIGN_T,
	TOKEN_OP_BIT_OR_ASSIGN_T,
	TOKEN_OP_BIT_XOR_ASSIGN_T,
	TOKEN_OP_MOD_ASSIGN_T,
	TOKEN_OP_PTR_ADD_T,
	TOKEN_OP_EQ_T,
	TOKEN_OP_NEQ_T,
	TOKEN_OP_LEQ_T,
	TOKEN_OP_GEQ_T,
	TOKEN_OP_INC_T,
	TOKEN_OP_DEC_T,
	TOKEN_OP_ARROW_T,
	TOKEN_OP_SHR_T,
	TOKEN_OP_SHL_T,
	TOKEN_OP_PTR_ADD_ASSIGN_T,
	TOKEN_OP_SHL_ASSIGN_T,
	TOKEN_OP_SHR_ASSIGN_T,
	TOKEN_OP_NONE_T
};

u32 token_op_str_to_enum(char *str);
void token_list_append(token_list_t *lst, token_t tok);
token_list_t *new_token_list();

token_list_t *lexe(char *text);
void token_print(token_t tok);
void token_free(token_t tok);
void token_list_free(token_list_t *lst);
void token_list_append(token_list_t *lst, token_t tok);

#endif