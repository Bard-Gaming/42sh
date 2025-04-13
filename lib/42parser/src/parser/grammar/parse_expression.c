/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_expression
*/

#include <42parser/parser.h>
#include <42parser/error.h>


/*
** Parses an expression.
** Expressions are either pipelines
** or atoms.
*/
ast_t *parse_expression(parser_t *parser)
{
    return parse_binary_operation(parser);
}
