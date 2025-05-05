/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Header file for
** lexer tokens
*/

#ifndef PARSER_TOKEN_H
    #define PARSER_TOKEN_H

    #define _RANGE(val, start, end) (start <= val && val <= end)
    #define IS_REDIRECT(t) _RANGE(t, TT_REDIRECT_IN, TT_REDIRECT_APPEND)
    #define IS_ARGUMENT(t) _RANGE(t, TT_RAW_ARGUMENT, TT_ARGUMENT)
    #define IS_COMMAND_TOKEN(t) (IS_REDIRECT(t) || IS_ARGUMENT(t))

    #include <stdbool.h>
    #include <stddef.h>


typedef enum {
    TT_ERROR,

    // Single char:
    TT_AMPERSAND,         // &
    TT_LPAREN,            // (
    TT_RPAREN,            // )
    TT_PIPE,              // |

    // Two chars:
    TT_AND,               // &&
    TT_OR,                // ||

    // Redirections:
    TT_REDIRECT_IN,       // [fd]?<[&fd]?
    TT_REDIRECT_HEREDOC,  // [fd]?<<
    TT_REDIRECT_HERESTR,  // [fd]?<<<
    TT_REDIRECT_OUT,      // [fd]?>[&fd]?
    TT_REDIRECT_APPEND,   // [fd]?>>

    // Arguments:
    TT_RAW_ARGUMENT,      // raw arguments (no interpretation needed)
    TT_ARGUMENT_STR,      // arguments which need to be interpreted
    TT_ARGUMENT,          // arguments which need to be interpreted (no ws)

    // Keywords:
    TT_IF,
    TT_THEN,
    TT_ELSE,
    TT_ENDIF,

    // Misc.:
    TT_SEPARATOR,         // Statement separator, i.e. '\n' or ';'
    TT_EOF,
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
