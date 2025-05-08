/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_subatom
*/

#include <42parser/parser.h>
#include <42parser/ast.h>
#include <42parser/token.h>
#include <42parser/error.h>


/*
** Sets an error message appropriate to
** token that caused the error.
*/
static void set_error(const parser_t *parser)
{
    switch (parser->current->type) {
    case TT_RPAREN:
        return parser_errno_set(PE_UNMATCHED_RPAREN);
    default:
        return parser_errno_set(PE_NULL_COMMAND);
    }
}

/*
** Parses a subatom.
** Subatoms should be reserved as the
** nodes that are contained within a command.
** These nodes are:
** - Arguments
** - Redirections (all kinds)
*/
ast_t *parse_subatom(parser_t *parser)
{
    switch (parser->current->type) {
    case TT_REDIRECT_HEREDOC:
        return parse_redirect_non_fd(parser, RT_HEREDOC_END);
    case TT_REDIRECT_HERESTR:
        return parse_redirect_non_fd(parser, RT_HERESTRING);
    case TT_REDIRECT_APPEND:
        return parse_redirect_append(parser);
    case TT_REDIRECT_OUT:
        return parse_redirect_out(parser);
    case TT_REDIRECT_IN:
        return parse_redirect_in(parser);
    case TT_ARGUMENT:
        return parse_argument(parser);
    case TT_EOF:
        return ast_create(AT_ERROR);
    default:
        set_error(parser);
        return ast_create(AT_ERROR);
    }
}
