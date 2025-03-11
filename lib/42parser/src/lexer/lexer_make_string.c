/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** lexer_make_string
*/

#include <42parser/lexer.h>
#include <42parser/token.h>
#include <stdbool.h>


static bool is_string_end(char c, char quote)
{
    return
        c == '\n' ||
        c == '\0' ||
        c == quote;
}

/*
** Make a string token.
** Returns an error token instead
** if the string is unmatched.
** The resulting token doesn't include
** the quote chars.
*/
token_t *lexer_make_string(lexer_t *lexer)
{
    char quote = lexer_consume();

    lexer->start++;
    while (!is_string_end(*lexer->current, quote))
        lexer->current++;
    if (*lexer->current != quote)
        return token_create(TT_ERROR, NULL, 0);
    lexer->current++;
    return token_create(
        TT_ARGUMENT, lexer->start,
        lexer->current - 1 - lexer->start
    );
}
