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


static void update_keyword(token_t *token,
    const char *keyword, token_type_t type)
{
    if (strncmp(token->start, keyword, strlen(keyword)) == 0)
        token->type = type;
}

/*
** Checks for keywords with 4 characters.
*/
static void check_keyword_4(token_t *token)
{
    switch (*token->start) {
    case 'e':
        return update_keyword(token, "else", TT_ELSE);
    case 't':
        return update_keyword(token, "then", TT_THEN);
    }
}

/*
** Updates the given token to be a
** keyword token if it matches a keyword
*/
void lexer_check_keyword(token_t *token)
{
    switch (token->length) {
    case 2:
        return update_keyword(token, "if", TT_IF);
    case 4:
        return check_keyword_4(token);
    case 5:
        return update_keyword(token, "endif", TT_ENDIF);
    }
}
