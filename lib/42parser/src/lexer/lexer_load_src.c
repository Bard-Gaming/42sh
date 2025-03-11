/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** lexer_load_src
*/

#include <42parser/lexer.h>


void lexer_load_src(const char *src)
{
    lexer_t *lexer = lexer_get();

    lexer->start = src;
    lexer->current = src;
}
