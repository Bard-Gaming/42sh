/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** lexer_consume
*/

#include <42parser/lexer.h>


char lexer_consume(void)
{
    lexer_t *lexer = lexer_get();
    char consumed = *lexer->current;

    lexer->current++;
    return consumed;
}
