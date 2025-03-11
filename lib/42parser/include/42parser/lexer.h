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


typedef struct {
    const char *start;
    const char *current;
} lexer_t;


lexer_t *lexer_get(void);
void lexer_load_src(const char *src);
char lexer_consume(void);
token_t *lexer_scan(void);


// Token generation:
token_t *lexer_make_generic(lexer_t *lexer, token_type_t type);
token_t *lexer_make_operator(lexer_t *lexer, token_type_t type);
token_t *lexer_make_string(lexer_t *lexer);
token_t *lexer_make_argument(lexer_t *lexer);


#endif
