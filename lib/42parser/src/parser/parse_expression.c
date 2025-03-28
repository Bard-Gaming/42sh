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
** Returns an AT_ERROR node and sets
** P_ERRNO on error.
*/
ast_t *parse_expression(parser_t *parser)
{
    ast_t *atom = parse_atom(parser);

    if (parser->current->type == TT_PIPE)
        atom = parse_pipeline(parser, atom);
    return atom;
}
