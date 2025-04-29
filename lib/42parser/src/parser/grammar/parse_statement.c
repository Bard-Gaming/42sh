/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_statement
*/

#include <42parser/parser.h>


/*
** Parse a statement.
** Statements can be expressions, meaning
** that if no statement tokens are present,
** an expression is parsed instead.
*/
ast_t *parse_statement(parser_t *parser)
{
    switch (parser->current->type) {
    case TT_IF:
        return parse_if_statement(parser);
    default:
        return parse_expression(parser);
    }
}
