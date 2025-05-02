/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Header file for
** everything related to
** the lexer
*/

#ifndef PARSER_LEXER_H
    #define PARSER_LEXER_H
    #include <42parser/token.h>
    #include <42parser/error.h>
    #include <stdbool.h>


typedef struct {
    const char *start;
    const char *current;
} lexer_t;


// Lexer:
void lexer_load_src(lexer_t *lexer, const char *src);
char lexer_consume(lexer_t *lexer);
token_t *lexer_scan(lexer_t *lexer);

// Token generation:
token_t *lexer_make_generic(lexer_t *lexer, token_type_t type);
token_t *lexer_make_operator(lexer_t *lexer, token_type_t type);
token_t *lexer_make_raw_argument(lexer_t *lexer);
token_t *lexer_make_argument(lexer_t *lexer);
token_t *lexer_make_argument_str(lexer_t *lexer);
token_t *lexer_make_redirect_in(lexer_t *lexer);
token_t *lexer_make_redirect_out(lexer_t *lexer);
token_t *lexer_make_argument(lexer_t *lexer);
token_t *lexer_make_error(parser_errno_t error);

// Utils:
void lexer_check_keyword(token_t *token);
bool lexer_is_whitespace(char c);
bool lexer_is_argument_char(char c);
bool lexer_is_redirect_in(const lexer_t *lexer);
bool lexer_is_redirect_out(const lexer_t *lexer);


#endif
