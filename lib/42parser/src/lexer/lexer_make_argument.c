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


static bool is_subargument_end(const lexer_t *lexer, char quote)
{
    return
        *lexer->current == '\n' ||
        *lexer->current == '\0' ||
        *lexer->current == quote;
}

static bool unmatched_quote_error(char quote)
{
    switch (quote) {
    case '`':
        parser_errno_set(PE_UNMATCHED_BACKTICK);
        break;
    case '\'':
        parser_errno_set(PE_UNMATCHED_RAW_STRING);
        break;
    case '"':
        parser_errno_set(PE_UNMATCHED_FORMAT_STRING);
        break;
    }
    return false;
}

static bool is_escape(const lexer_t *lexer)
{
    return
        *lexer->current == '\\' &&
        *(lexer->current + 1) != '\n' &&
        *(lexer->current + 1) != '\0';
}

static bool add_subargument(lexer_t *lexer)
{
    char quote = *lexer->current;

    lexer->current++;
    while (!is_subargument_end(lexer, quote)) {
        if (is_escape(lexer))
            lexer->current++;
        lexer->current++;
    }
    if (*lexer->current != quote)
        return unmatched_quote_error(quote);
    lexer->current++;
    return true;
}

static bool is_quote(char c)
{
    return
        c == '\'' ||
        c == '"' ||
        c == '`';
}

static bool add_element(lexer_t *lexer)
{
    if (is_quote(*lexer->current))
        return add_subargument(lexer);
    if (is_escape(lexer))
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
