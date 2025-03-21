/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_expression
*/

#include "42parser/token.h"
#include <42parser/parser.h>
#include <42parser/error.h>


/*
** Parses an expression.
** Returns an AT_ERROR node and sets
** P_ERRNO on error.
*/
ast_t *parse_expression(parser_t *parser)
{
    switch (parser->current->type) {
    case TT_ARGUMENT:
        return parse_command(parser);
    case TT_LPAREN:
        return parse_parenthesis(parser);
    case TT_EOF:
        return ast_create(AT_ERROR);
    default:
        parser_errno_set(PE_WRONG_SYNTAX);
        return ast_create(AT_ERROR);
    }
}
