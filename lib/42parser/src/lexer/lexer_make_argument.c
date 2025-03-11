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
    while (lexer_is_argument(*lexer->current))
        lexer->current++;
    return token_create(
        TT_ARGUMENT, lexer->start,
        lexer->current - lexer->start
    );
}
