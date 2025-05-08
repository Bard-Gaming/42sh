/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** preparser_add_token
*/

#include <42parser/preparser.h>
#include <string.h>


/*
** Adds a the preparser's current token's value
** to the output.
** TODO: Optimize growth
*/
void preparser_add_token(preparser_t *preparser)
{
    token_t *token = preparser->current;
    char *dest;

    while (preparser->count + token->length + 1 >= preparser->capacity)
        preparser_grow(preparser);
    dest = preparser->output + preparser->count;
    memcpy(dest, token->start, token->length);
    preparser->count += token->length;
    preparser->output[preparser->count] = '\0';
}
