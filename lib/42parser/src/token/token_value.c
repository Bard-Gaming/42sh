/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** token_value
*/

#include <42parser/token.h>
#include <stdlib.h>
#include <string.h>


/*
** Function that counts the amount of
** characters that match c within the
** given string.
*/
static size_t count_occurrences(char c, const char *str, size_t len)
{
    size_t result = 0;

    for (size_t i = 0; i < len; i++)
        if (c == str[i])
            result++;
    return result;
}

/*
** Duplicate a token's value into
** a newly allocated, null terminated,
** sanitized string.
** A sanitized string is just a string
** without backslashes, in this case.
*/
static char *get_sanitized_value(const token_t *token)
{
    size_t escape_count = count_occurrences('\\', token->start, token->length);
    char *value = malloc((token->length - escape_count + 1) * sizeof(char));
    char *current = value;

    if (value == NULL)
        return NULL;
    for (size_t i = 0; i < token->length; i++) {
        if (token->start[i] == '\\')
            continue;
        *current = token->start[i];
        current++;
    }
    *current = '\0';
    return value;
}

/*
** Duplicate a token's value into
** a newly allocated, null terminated
** string.
** Returns NULL on error.
*/
char *token_value(const token_t *token)
{
    char *value;

    if (token->should_sanitize)
        return get_sanitized_value(token);
    value = malloc((token->length + 1) * sizeof(char));
    if (value == NULL)
        return NULL;
    memcpy(value, token->start, token->length);
    value[token->length] = '\0';
    return value;
}
