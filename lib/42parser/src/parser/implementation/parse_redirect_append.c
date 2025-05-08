/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_redirect_append
*/

#include <42parser/parser.h>
#include <42parser/ast.h>
#include <42parser/error.h>
#include <fcntl.h>
#include <stdlib.h>


static void create_redirect_new_file(ast_redirect_t *redirect,
    parser_t *parser)
{
    parser_next(parser);
    redirect->type = RT_FILE_PATH;
    redirect->open_flags = O_CREAT | O_WRONLY | O_APPEND;
    redirect->new_fd.path = parse_subatom(parser);
}

ast_t *parse_redirect_append(parser_t *parser)
{
    ast_t *node = ast_create(AT_REDIRECT);
    ast_redirect_t *redirect;

    if (parser->next->type != TT_ARGUMENT) {
        parser_errno_set(PE_MISSING_REDIRECT_NAME);
        node->type = AT_ERROR;
        return node;
    }
    redirect = malloc(sizeof(ast_redirect_t));
    node->data = redirect;
    redirect->old_fd = *parser->current->start == '>' ?
        1 : atoi(parser->current->start);
    create_redirect_new_file(redirect, parser);
    return node;
}
