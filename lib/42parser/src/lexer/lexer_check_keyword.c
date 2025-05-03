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
    switch (token->length) {
    case 2:
        if (strncmp(token->start, "if", 2) == 0)
            update_token(token, TT_IF);
        return;
    case 4:
        if (strncmp(token->start, "then", 4) == 0)
            update_token(token, TT_THEN);
        return;
    case 5:
        if (strncmp(token->start, "endif", 5) == 0)
            update_token(token, TT_ENDIF);
        return;
    }
}
