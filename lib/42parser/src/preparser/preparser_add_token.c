/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** preparser_add_token
*/

#include "42parser/token.h"
#include <42parser/preparser.h>
#include <string.h>


static void copy_str(char *dest, const token_t *token, char quote)
{
    *dest = quote;
    dest = mempcpy(dest + 1, token->start, token->length);
    *dest = quote;
}

static void copy_token(char *dest, const token_t *token)
{
    switch (token->type) {
    case TT_RAW_ARGUMENT:
        return copy_str(dest, token, '\'');
    case TT_ARGUMENT_STR:
        return copy_str(dest, token, '"');
    default:
        memcpy(dest, token->start, token->length);
        return;
    }
}

static size_t get_token_length(const token_t *token)
{
    switch (token->type) {
    case TT_RAW_ARGUMENT:
    case TT_ARGUMENT_STR:
        return token->length + 2;
    default:
        return token->length;
    }
}

/*
** Adds a the preparser's current token's value
** to the output.
** TODO: Optimize growth
*/
void preparser_add_token(preparser_t *preparser)
{
    token_t *token = preparser->current;
    size_t token_len = get_token_length(token);

    while (preparser->count + token_len + 1 >= preparser->capacity)
        preparser_grow(preparser);
    copy_token(preparser->output + preparser->count, token);
    preparser->count += token_len;
    preparser->output[preparser->count] = '\0';
}
