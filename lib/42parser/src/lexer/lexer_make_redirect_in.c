/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** lexer_make_redirect_in
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
** Makes either a heredoc, a herestring,
** or an error token based on the given
** input.
*/
static token_t *make_non_fd_token(lexer_t *lexer)
{
    if (*(lexer->current + 1) != '<') {
        if (*(lexer->current + 1) == '&')
            return lexer_make_error(PE_REDIRECT_WITH_ILLEGAL_FD);
        return lexer_make_generic(lexer, TT_REDIRECT_HEREDOC);
    }
    lexer->current++;
    if (*(lexer->current + 1) == '&')
        return lexer_make_error(PE_REDIRECT_WITH_ILLEGAL_FD);
    return lexer_make_generic(lexer, TT_REDIRECT_HERESTR);
}

/*
** Make an input redirection token.
*/
token_t *lexer_make_redirect_in(lexer_t *lexer)
{
    scan_file_descriptor(lexer);
    lexer->current++;
    if (*lexer->current == '<')
        return make_non_fd_token(lexer);
    if (*lexer->current == '&') {
        lexer->current++;
        if (!('0' <= *lexer->current && *lexer->current <= '9'))
            return syntax_error();
        scan_file_descriptor(lexer);
    }
    return token_create(
        TT_REDIRECT_IN, lexer->start,
        lexer->current - lexer->start
    );
}
