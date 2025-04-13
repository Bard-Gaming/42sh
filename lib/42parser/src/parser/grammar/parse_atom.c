/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_atom
*/

#include <42parser/parser.h>
#include <42parser/error.h>


/*
** Parses an atom.
** Atoms are either commands,
** or command compounds.
** Returns an error node if
** the current token doesn't
** correspond to any of the
** aforementioned nodes.
*/
ast_t *parse_atom(parser_t *parser)
{
    if (parser->current->type == TT_LPAREN)
        return parse_parenthesis(parser);
    if (IS_COMMAND_NODE(parser->current->type))
        return parse_command(parser);
    parser_errno_set(PE_NULL_COMMAND);
    return ast_create(AT_ERROR);
}
