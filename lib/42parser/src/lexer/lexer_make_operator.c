/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** lexer_make_operator
*/

#include <42parser/lexer.h>
#include <42parser/token.h>


token_t *lexer_make_operator(lexer_t *lexer, token_type_t type)
{
    lexer->current += 2;
    return token_create(
        type, lexer->start,
        lexer->current - lexer->start
    );
}
