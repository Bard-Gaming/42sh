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


static bool is_substitution_end(const lexer_t *lexer)
{
    return
        *lexer->current == '\n' ||
        *lexer->current == '\0' ||
        *lexer->current == '`';
}

static bool add_substitution(lexer_t *lexer)
{
    lexer->current++;
    while (!is_substitution_end(lexer))
        lexer->current++;
    if (*lexer->current != '`') {
        parser_errno_set(PE_UNMATCHED_BACKTICK);
        return false;
    }
    lexer->current++;
    return true;
}

static bool add_element(lexer_t *lexer)
{
    if (*lexer->current == '`')
        return add_substitution(lexer);
    if (*lexer->current == '\\' && *(lexer->current + 1) != '\0')
        lexer->current++;
    lexer->current++;
    return true;
}

token_t *lexer_make_argument(lexer_t *lexer)
{
    token_t *token;

    while (lexer_is_argument_char(*lexer->current))
        if (!add_element(lexer))
            return token_create(TT_ERROR, NULL, 0);
    token = token_create(
        TT_ARGUMENT, lexer->start,
        lexer->current - lexer->start
    );
    return token;
}
