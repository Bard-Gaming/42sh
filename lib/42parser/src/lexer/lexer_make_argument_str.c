/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** lexer_make_argument_str
*/

#include <42parser/lexer.h>
#include <42parser/token.h>
#include <42parser/error.h>
#include <stdbool.h>


static bool is_string_end(char c)
{
    return
        c == '\n' ||
        c == '\0' ||
        c == '"';
}

/*
** Make a format string token.
** Returns an error token instead
** if the string is unmatched.
** The resulting token doesn't include
** the double quotes.
*/
token_t *lexer_make_argument_str(lexer_t *lexer)
{
    lexer->start++;
    lexer->current++;
    while (!is_string_end(*lexer->current))
        lexer->current++;
    if (*lexer->current != '"')
        return lexer_make_error(PE_UNMATCHED_FORMAT_STRING);
    lexer->current++;
    return token_create(
        TT_ARGUMENT, lexer->start,
        lexer->current - 1 - lexer->start
    );
}
