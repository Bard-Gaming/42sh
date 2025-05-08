/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_redirect_heredoc
*/

#include <42parser/parser.h>
#include <42parser/ast.h>
#include <42parser/error.h>
#include <stdlib.h>


/*
** Sets the appropriate error depending
** on the given type.
*/
static void set_error(redirect_type_t type)
{
    switch (type) {
    case RT_HEREDOC_END:
        return parser_errno_set(PE_EMPTY_HEREDOC);
    case RT_HERESTRING:
        return parser_errno_set(PE_EMPTY_HERESTR);
    default:
        return parser_errno_set(PE_MISSING_REDIRECT_NAME);
    }
}

/*
** Parses a redirection which
** doesn't take a file descriptor.
** This is used for parsing both
** heredocs and herestrings, as both
** are equal when it comes to how they
** are parsed.
*/
ast_t *parse_redirect_non_fd(parser_t *parser, redirect_type_t type)
{
    ast_t *node = ast_create(AT_REDIRECT);
    ast_redirect_t *redirect;

    if (parser->next->type != TT_ARGUMENT) {
        set_error(type);
        node->type = AT_ERROR;
        return node;
    }
    redirect = malloc(sizeof(ast_redirect_t));
    node->data = redirect;
    redirect->old_fd = *parser->current->start == '<' ?
        0 : atoi(parser->current->start);
    parser_next(parser);
    redirect->type = type;
    redirect->new_fd.path = parse_subatom(parser);
    return node;
}
