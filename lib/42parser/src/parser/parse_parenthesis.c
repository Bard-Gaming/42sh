/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_parenthesis
*/

#include <42parser/parser.h>


/*
** Parses a parenthesis.
** Returns an AT_ERROR node on error
** (notably when the parenthesis is unmatched).
*/
ast_t *parse_parenthesis(parser_t *parser)
{
    ast_t *result;

    parser_next(parser);
    result = parse_statement(parser);
    if (parser->current->type == TT_RPAREN) {
        parser_next(parser);
        return result;
    }
    ast_delete(result);
    return ast_create(AT_ERROR);
}
