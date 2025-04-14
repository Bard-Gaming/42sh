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
** Sets the appropriate error depending
** on the current illegal token.
*/
static void set_error(parser_t *parser)
{
    switch (parser->current->type) {
    case TT_RPAREN:
        return parser_errno_set(PE_UNMATCHED_RPAREN);
    default:
        return parser_errno_set(PE_NULL_COMMAND);
    }
}

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
        return parse_compound(parser);
    if (IS_COMMAND_NODE(parser->current->type))
        return parse_command(parser);
    set_error(parser);
    return ast_create(AT_ERROR);
}
