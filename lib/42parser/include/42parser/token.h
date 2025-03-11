/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Header file for
** lexer tokens
*/

#ifndef PARSER_TOKEN_H
    #define PARSER_TOKEN_H
    #include <stddef.h>
    #define ARGUMENT_NON_ALPHA_NUM_CHARS "%./+=-@!^$?:_"


typedef enum {
    TT_ERROR,

    // Single char:
    TT_LPAREN,
    TT_RPAREN,
    TT_SEMICOLON,
    TT_JOB,
    TT_PIPE,

    // Two chars:
    TT_AND,
    TT_OR,

    TT_ARGUMENT,
} token_type_t;


typedef struct {
    token_type_t type;
    const char *start;
    size_t length;
} token_t;


token_t *token_create(token_type_t type, const char *start, size_t length);
char *token_value(const token_t *token);
void token_delete(token_t *token);


#endif
