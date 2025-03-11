/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_atom
*/

#include <42parser/parser.h>


/*
** Parses an atom.
** Returns an AT_ERROR node on error.
*/
ast_t *parse_atom(parser_t *parser)
{
    switch (parser->current->type) {
    case TT_ARGUMENT:
        return parse_command(parser);
    case TT_LPAREN:
        return parse_parenthesis(parser);
    default:
        return ast_create(AT_ERROR);
    }
}
