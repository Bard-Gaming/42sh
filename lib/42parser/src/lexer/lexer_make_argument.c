/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** lexer_make_argument
*/

#include <42parser/lexer.h>
#include <42parser/token.h>
#include <stdbool.h>


token_t *lexer_make_argument(lexer_t *lexer)
{
    token_t *token;

    while (lexer_is_argument_char(*lexer->current)) {
        if (*lexer->current == '\\' && *(lexer->current + 1) != '\0')
            lexer->current++;
        lexer->current++;
    }
    token = token_create(
        TT_ARGUMENT, lexer->start,
        lexer->current - lexer->start
    );
    token->should_sanitize = true;
    return token;
}
