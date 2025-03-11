/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** lexer_get
*/

#include <42parser/lexer.h>


lexer_t *lexer_get(void)
{
    static lexer_t lexer = {
        .start = NULL,
        .current = NULL,
    };

    return &lexer;
}
