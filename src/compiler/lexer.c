#include "compiler/tokens.h"
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include "compiler/errors.h"

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

static int is_syntax(char c) {
	for (int i = 0; tokens_syntax[i] != NULL; i++) {
		if (tokens_syntax[i][0] == c)
			return i;
	}
	return -1;
}



token_list_t *lexe(char *text) {
	uint idx = 0;
	int line = 1;
	token_list_t *res = new_token_list();
	if (res == NULL) {
		add_error(ERR_LEXE_OUT_OF_MEMORY);
		return NULL;
	}
	while (text[idx] != '\0') {
		if (text[idx] == '\n') {
			line++;
			idx++;
		}
		else if (is_lexer_skip(text[idx]))
			idx++;
		else if (text[idx] == '/' && text[idx + 1] == '/') {
			idx += 2;
			while (text[idx] != '\n' && text[idx] != '\0')
				idx++;
		}
		else if (text[idx] == '/' && text[idx + 1] == '*') {
			idx += 2;
			while (text[idx] != '\0' && text[idx] != '*' && text[idx + 1] != '/')
				idx++;
			idx += 2;
		}
		else if ('0' <= text[idx] && text[idx] <= '9') {
			uint num_start = idx;
			while ('0' <= text[idx] && text[idx] <= '9')
				idx++;
			if (text[idx] == '.') {
				idx++;
				while ('0' <= text[idx] && text[idx] <= '9')
					idx++;
			}
			char *num = malloc(idx - num_start + 1);
			if (num == NULL) {
				token_list_free(res);
				add_error(ERR_LEXE_OUT_OF_MEMORY);
				return NULL;
			}
			memcpy(num, &text[num_start], idx - num_start);
			num[idx - num_start] = '\0';
			token_list_append(res, (token_t){TOKEN_INT_T, {.i = atoi(num)}, line});
			free(num);
		}
		else if (is_syntax(text[idx]) != -1) {
			token_list_append(res, (token_t){.line = line, .type = TOKEN_SYNTAX_T, .val = {.syntax = is_syntax(text[idx])}});
			idx++;
		}
		else if (text[idx] == '"') {
			idx++;
			uint str_start = idx;
			while (text[idx] != '"' && text[idx] != '\0' && !(text[idx] == '"' && text[idx - 1] == '\\'))
				idx++;
			if (text[idx] != '"') {
				token_list_free(res);
				add_error(ERR_LEXE_MISSING_CLOSING_DOUBLE_QUOTE);
				return NULL;
			}
			char *str = malloc(idx - str_start + 1);
			if (str == NULL) {
				token_list_free(res);
				add_error(ERR_LEXE_OUT_OF_MEMORY);
				return NULL;
			}
			memcpy(str, &text[str_start], idx - str_start);
			str[idx - str_start] = '\0';
			token_list_append(res, (token_t){TOKEN_STR_T, {str}, line});
			idx++;
		}
		else if (text[idx] == '\'') {
			idx++;
			uint str_start = idx;
			while (text[idx] != '\'' && text[idx] != '\0' && !(text[idx] == '\'' && text[idx - 1] == '\\'))
				idx++;
			if (text[idx] != '\'') {
				token_list_free(res);
				add_error(ERR_LEXE_MISSING_CLOSING_SINGLE_QUOTE);
				return NULL;
			}
			char *str = malloc(idx - str_start + 1);
			if (str == NULL) {
				token_list_free(res);
				add_error(ERR_LEXE_OUT_OF_MEMORY);
				return NULL;
			}
			memcpy(str, &text[str_start], idx - str_start);
			str[idx - str_start] = '\0';
			token_list_append(res, (token_t){TOKEN_STR_T, {str}, line});
			idx++;
		}
		else if (token_op_str_to_enum(&text[idx]) != TOKEN_OP_NONE_T) {
			token_list_append(res, (token_t){TOKEN_OPERATOR_T, {.op = token_op_str_to_enum(&text[idx])}, line});
			if (res->tokens[res->len - 1].val.op < tokens_op1_len)
				idx += 1;
			else if (res->tokens[res->len - 1].val.op < tokens_op1_len + tokens_op2_len)
				idx += 2;
			else
				idx += 3;
		}
		else {
			// check if it is an identifier (starts with non digit and contain no syntax characters)
			if ((text[idx] >= 'a' && text[idx] <= 'z') || (text[idx] >= 'A' && text[idx] <= 'Z')) {
				uint id_start = idx;
				while ((text[idx] >= 'a' && text[idx] <= 'z') || (text[idx] >= 'A' && text[idx] <= 'Z') || (text[idx] >= '0' && text[idx] <= '9'))
					idx++;
				char *id = malloc(idx - id_start + 1);
				if (id == NULL) {
					token_list_free(res);
					add_error(ERR_LEXE_OUT_OF_MEMORY);
					return NULL;
				}
				memcpy(id, &text[id_start], idx - id_start);
				id[idx - id_start] = '\0';
				token_list_append(res, (token_t){TOKEN_IDENTIFIER_T, {.id = id}, line});
			}
			else {
				printf("idx = %d %d %c%c%c\n", idx, line, text[idx], text[idx + 1], text[idx + 2]);
				add_error(ERR_LEXE_UNEXPECTED_TOKEN);
				token_list_free(res);
				return NULL;
			}
		}
	}
	// add token_none at the end of res
	token_list_append(res, (token_t){TOKEN_NONE_T, {0}, line});
	res->len -= 1;
	return res;
}