/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_command
*/

#include <42parser/parser.h>
#include <42parser/token.h>


/*
** Parses a command.
** Returns an error node on error.
*/
ast_t *parse_command(parser_t *parser)
{
    ast_t *node = ast_create(AT_COMMAND);
    ast_command_t *command = ast_command_create();

    node->data = command;
    ast_command_append(command, parser->current);
    parser_next(parser);
    while (parser->current->type == TT_ARGUMENT) {
        ast_command_append(command, parser->current);
        parser_next(parser);
    }
    return node;
}
