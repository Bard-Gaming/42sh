/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** lexer_make_argument
*/

#include <42parser/lexer.h>
#include <42parser/token.h>
#include <stdbool.h>


static bool is_alphanumeric(char c)
{
    return
        ('a' <= c && c <= 'z') ||
        ('A' <= c && c <= 'Z') ||
        ('0' <= c && c <= '9');
}

static bool is_argument_char(char c)
{
    const char *current = ARGUMENT_NON_ALPHA_NUM_CHARS;

    if (is_alphanumeric(c))
        return true;
    while (*current != '\0') {
        if (c == *current)
            return true;
        current++;
    }
    return false;
}

token_t *lexer_make_argument(lexer_t *lexer)
{
    while (is_argument_char(*lexer->current))
        lexer->current++;
    return token_create(
        TT_ARGUMENT, lexer->start,
        lexer->current - lexer->start
    );
}
