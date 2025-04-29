/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** lexer_check_keyword
*/

#include <42parser/lexer.h>
#include <42parser/token.h>
#include <string.h>


static void update_token(token_t *token, token_type_t type)
{
    token->type = type;
    token->should_sanitize = false;
}

/*
** Updates the given token to be a
** keyword token if it matches a keyword
**
** TODO: Update this to be more optimized
*/
void lexer_check_keyword(token_t *token)
{
    if (strncmp(token->start, "if", token->length) == 0)
        return update_token(token, TT_IF);
    if (strncmp(token->start, "then", token->length) == 0)
        return update_token(token, TT_THEN);
    if (strncmp(token->start, "endif", token->length) == 0)
        return update_token(token, TT_ENDIF);
}
