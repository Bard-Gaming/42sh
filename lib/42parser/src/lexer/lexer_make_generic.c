/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** lexer_make_generic
*/

#include <42parser/lexer.h>
#include <42parser/token.h>


/*
** Make a generic token of the given type.
*/
token_t *lexer_make_generic(lexer_t *lexer, token_type_t type)
{
    lexer->current++;
    return token_create(
        type, lexer->start,
        lexer->current - lexer->start
    );
}
