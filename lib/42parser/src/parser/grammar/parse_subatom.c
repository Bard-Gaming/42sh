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
** Utility function to parse all
** kinds of redirections.
** Note: the default case will
** never happen, and only exists
** to avoid parser errors.
*/
static ast_t *parse_redirect(parser_t *parser)
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
    default:
        return NULL;
    }
}

/*
** Parses a subatom.
** Subatoms should be reserved as the
** nodes that are contained within a command.
** These nodes are:
** - Arguments
** - Raw strings
** - Format strings
** - Redirections (all kinds)
*/
ast_t *parse_subatom(parser_t *parser)
{
    switch (parser->current->type) {
    case TT_REDIRECT_HEREDOC:
    case TT_REDIRECT_HERESTR:
    case TT_REDIRECT_APPEND:
    case TT_REDIRECT_OUT:
    case TT_REDIRECT_IN:
        return parse_redirect(parser);
    case TT_RAW_STRING:
    case TT_FORMAT_STRING:
    case TT_ARGUMENT:
        return parse_argument(parser);
    case TT_EOF:
        return ast_create(AT_ERROR);
    default:
        parser_errno_set(PE_NULL_COMMAND);
        return ast_create(AT_ERROR);
    }
}
