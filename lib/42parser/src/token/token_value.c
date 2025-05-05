/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** token_value
*/

#include <42parser/token.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


/*
** Duplicate a token's value into
** a newly allocated, null terminated
** string.
** Returns NULL on error.
*/
char *token_value(const token_t *token)
{
    char *result = strndup(token->start, token->length);

    if (result == NULL) {
        fputs("42parser: critical memory error\n", stderr);
        exit(84);
    }
    return result;
}
