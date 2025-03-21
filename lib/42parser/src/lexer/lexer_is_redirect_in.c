/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** lexer_is_redirect_in
*/

#include <42parser/lexer.h>


/*
** Tells whether or not the next
** token is a redirection or not.
*/
bool lexer_is_redirect_in(const lexer_t *lexer)
{
    const char *current = lexer->start;

    while ('0' <= *current && *current <= '9')
        current++;
    return *current == '<';
}
