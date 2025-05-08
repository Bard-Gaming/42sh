/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** token_match
*/

#include <42parser/token.h>
#include <string.h>


/*
** Matches a given token to a given keyword.
** Returns whether or not the match was correct
** or not.
*/
bool token_match(const token_t *token, const char *keyword)
{
    size_t len;

    if (token->type != TT_ARGUMENT)
        return false;
    len = strlen(keyword);
    if (token->length != len)
        return false;
    return strncmp(token->start, keyword, len) == 0;
}
