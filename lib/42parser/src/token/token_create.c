/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** token_create
*/

#include <42parser/token.h>
#include <stdlib.h>


/*
** Create a token.
** Returns NULL on error.
*/
token_t *token_create(token_type_t type, const char *start, size_t length)
{
    token_t *token = malloc(sizeof(token_t));

    if (token == NULL)
        return NULL;
    token->type = type;
    token->start = start;
    token->length = length;
    return token;
}
