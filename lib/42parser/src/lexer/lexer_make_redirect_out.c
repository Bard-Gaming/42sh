/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** lexer_make_redirect_out
*/

#include <42parser/lexer.h>
#include <42parser/error.h>


static void scan_file_descriptor(lexer_t *lexer)
{
    while ('0' <= *lexer->current && *lexer->current <= '9')
        lexer->current++;
}

static token_t *syntax_error(void)
{
    parser_errno_set(PE_WRONG_SYNTAX);
    return token_create(TT_ERROR, NULL, 0);
}

/*
** Make an output redirection token.
*/
token_t *lexer_make_redirect_out(lexer_t *lexer)
{
    scan_file_descriptor(lexer);
    lexer->current++;
    if (*lexer->current == '>') {
        if (*(lexer->current + 1) == '&')
            return lexer_make_error(PE_REDIRECT_WITH_ILLEGAL_FD);
        return lexer_make_generic(lexer, TT_REDIRECT_APPEND);
    }
    if (*lexer->current == '&') {
        lexer->current++;
        if (!('0' <= *lexer->current && *lexer->current <= '9'))
            return syntax_error();
        scan_file_descriptor(lexer);
    }
    return token_create(
        TT_REDIRECT_OUT, lexer->start,
        lexer->current - lexer->start
    );
}
