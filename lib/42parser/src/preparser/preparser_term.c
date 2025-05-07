/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** preparser_term
*/

#include <42parser/preparser.h>
#include <stdlib.h>


/*
** Terminates / cleans up the preparser,
** Freeing all necessary values.
**
** Note: this does not free preparser->output,
** as the output should be freed by the user.
*/
void preparser_term(preparser_t *preparser)
{
    free(preparser->prev);
    free(preparser->current);
}
