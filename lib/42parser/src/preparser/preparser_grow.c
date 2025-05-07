/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** preparser_grow
*/

#include <42parser/preparser.h>
#include <stdlib.h>
#include <stdio.h>


/*
** Grows the preparser by the predefined
** growth factor.
*/
void preparser_grow(preparser_t *preparser)
{
    preparser->capacity = preparser->capacity > 0 ?
        preparser->capacity * PREPARSER_GROWTH_FACTOR :
        PREPARSER_INIT_CAP;
    preparser->output = reallocarray(
        preparser->output,
        preparser->capacity,
        sizeof(char)
    );
    if (preparser->output != NULL)
        return;
    fputs("42parser: critical memory error\n", stderr);
    exit(84);
}
