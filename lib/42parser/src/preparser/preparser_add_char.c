/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** preparser_add_char
*/

#include <42parser/preparser.h>


/*
** Adds a given character to the preparser.
*/
void preparser_add_char(preparser_t *preparser, char c)
{
    if (preparser->count + 2 >= preparser->capacity)
        preparser_grow(preparser);
    preparser->output[preparser->count] = c;
    preparser->count++;
    preparser->output[preparser->count] = '\0';
}
