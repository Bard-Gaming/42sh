/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** preparser_add_char
*/

#include <42parser/preparser.h>
#include <string.h>


/*
** Adds a given string to the preparser.
**
** Technical Addendum:
** memcpy is used here instead of strcpy as
** the length has already been computed,
** meaning it doesn't have to be computed
** again / taken into account by strcpy.
** TODO: Optimize growth
*/
void preparser_add_str(preparser_t *preparser, const char *str)
{
    size_t len = strlen(str);

    while (preparser->count + len + 1 >= preparser->capacity)
        preparser_grow(preparser);
    memcpy(preparser->output + preparser->count, str, len + 1);
    preparser->count += len;
}
