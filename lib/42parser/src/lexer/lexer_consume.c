/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** lexer_consume
*/

#include <42parser/lexer.h>


/*
** Consumes a given character,
** and moves on to the next.
*/
char lexer_consume(lexer_t *lexer)
{
    char consumed = *lexer->current;

    lexer->current++;
    return consumed;
}
