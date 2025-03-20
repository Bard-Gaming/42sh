/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_command
*/

#include <42parser/parser.h>
#include <42parser/token.h>
#include <42parser/error.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>


static bool is_command_node(const token_t *token)
{
    return
        token->type == TT_ARGUMENT ||
        token->type == TT_REDIRECT_OUT;
}

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

static void parse_argument(parser_t *parser, ast_command_t *command)
{
    ast_command_append(command, parser->current);
    parser_next(parser);
}

static void parse_output_file(parser_t *parser,
    ast_command_t *command, int redirect_fd)
{
    parser_next(parser);
    if (parser->current->type != TT_ARGUMENT) {
        parser_errno_set(PE_WRONG_SYNTAX);
        return;
    }
    command->is_path[redirect_fd] = true;
    command->io_files[redirect_fd] = token_value(parser->current);
    parser_next(parser);
}

static void parse_redirect(parser_t *parser, ast_command_t *command)
{
    const char *token_src = parser->current->start;
    int redirect_fd = 1;

    if (*token_src != '>')
        redirect_fd = consume_file_descriptor(&token_src);
    token_src++;
    if (*token_src == '>') {
        token_src++;
        command->open_flags[redirect_fd] = O_CREAT | O_WRONLY | O_APPEND;
    }
    if (*token_src != '&')
        return parse_output_file(parser, command, redirect_fd);
    token_src++;
    command->io_files[redirect_fd] =
        (void *)(intptr_t)consume_file_descriptor(&token_src);
    parser_next(parser);
}

/*
** Parse a command.
** Returns an error node on error.
*/
ast_t *parse_command(parser_t *parser)
{
    ast_t *node = ast_create(AT_COMMAND);
    ast_command_t *command = ast_command_create();

    node->data = command;
    ast_command_append(command, parser->current);
    parser_next(parser);
    while (is_command_node(parser->current)) {
        if (parser->current->type == TT_ARGUMENT)
            parse_argument(parser, command);
        else
            parse_redirect(parser, command);
    }
    return node;
}
