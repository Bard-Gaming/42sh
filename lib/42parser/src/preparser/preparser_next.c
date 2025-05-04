/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** preparser_next
*/

#include <42parser/preparser.h>
#include <stdlib.h>


/*
** Makes the preparser go on to the
** next token.
*/
void preparser_next(preparser_t *preparser)
{
    free(preparser->prev);
    preparser->prev = preparser->current;
    preparser->current = lexer_scan(&preparser->lexer);
}
