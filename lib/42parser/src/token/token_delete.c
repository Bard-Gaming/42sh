/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** token_delete
*/

#include <42parser/token.h>
#include <stdlib.h>


/*
** Delete a token.
*/
void token_delete(token_t *token)
{
    free(token);
}
