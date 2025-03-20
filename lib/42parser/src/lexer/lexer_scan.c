/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** lexer_scan
*/

#include "42parser/error.h"
#include <42parser/lexer.h>
#include <42parser/token.h>
#include <stdbool.h>


static token_t *scan_operations(lexer_t *lexer)
{
    switch (*lexer->start) {
    case '&':
        return *(lexer->start + 1) == '&' ?
            lexer_make_operator(lexer, TT_AND) :
            lexer_make_generic(lexer, TT_AMPERSAND);
    case '|':
        return *(lexer->start + 1) == '|' ?
            lexer_make_operator(lexer, TT_OR) :
            lexer_make_generic(lexer, TT_PIPE);
    default:
        break;
    }
    if (lexer_is_redirect_out(lexer))
        return lexer_make_redirect_out(lexer);
    if (lexer_is_argument(*lexer->start))
        return lexer_make_argument(lexer);
    return lexer_make_error(PE_ILLEGAL_CHAR);
}

static token_t *get_scanned_token(lexer_t *lexer)
{
    switch (*lexer->start) {
    case '"':
    case '\'':
        return lexer_make_string(lexer);
    case '(':
        return lexer_make_generic(lexer, TT_LPAREN);
    case ')':
        return lexer_make_generic(lexer, TT_RPAREN);
    case ';':
        return lexer_make_generic(lexer, TT_SEMICOLON);
    default:
        return scan_operations(lexer);
    }
}

static void skip_whitespace(lexer_t *lexer)
{
    while (lexer_is_whitespace(*lexer->start))
        lexer->start++;
    lexer->current = lexer->start;
}

/*
** Scan a single token.
** Returns NULL if no source has,
** been loaded, and an error token
** on other errors.
*/
token_t *lexer_scan(void)
{
    lexer_t *lexer = lexer_get();

    lexer->start = lexer->current;
    if (lexer->start == NULL)
        return NULL;
    skip_whitespace(lexer);
    if (*lexer->start == '\0')
        return token_create(TT_EOF, NULL, 0);
    return get_scanned_token(lexer);
}
