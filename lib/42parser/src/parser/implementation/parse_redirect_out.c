/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_redirect_out
*/

#include <42parser/parser.h>
#include <42parser/ast.h>
#include <42parser/error.h>
#include <fcntl.h>
#include <stdlib.h>


static int consume_file_descriptor(const char **src)
{
    int fd = 0;

    while ('0' <= **src && **src <= '9') {
        fd *= 10;
        fd += **src - '0';
        (*src)++;
    }
    return fd;
}

static void create_redirect_new_fd(parser_t *parser,
    ast_redirect_t *redirect, const char **src)
{
    (*src)++;
    redirect->type = RT_FILE_DESCRIPTOR;
    redirect->new_fd.fd = consume_file_descriptor(src);
    parser_next(parser);
}

static void create_redirect_new_file(parser_t *parser,
    ast_redirect_t *redirect)
{
    parser_next(parser);
    if (!IS_ARGUMENT(parser->current->type)) {
        parser_errno_set(PE_MISSING_REDIRECT_NAME);
        redirect->type = RT_FILE_DESCRIPTOR;
        return;
    }
    redirect->type = RT_FILE_PATH;
    redirect->open_flags = O_CREAT | O_WRONLY | O_TRUNC;
    redirect->new_fd.path = parse_subatom(parser);
}

ast_t *parse_redirect_out(parser_t *parser)
{
    ast_t *node = ast_create(AT_REDIRECT);
    ast_redirect_t *redirect = malloc(sizeof(ast_redirect_t));
    const char *token_src = parser->current->start;

    node->data = redirect;
    redirect->old_fd = *token_src == '>' ?
        1 : consume_file_descriptor(&token_src);
    token_src++;
    if (*token_src == '&')
        create_redirect_new_fd(parser, redirect, &token_src);
    else
        create_redirect_new_file(parser, redirect);
    return node;
}
