/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_command
*/

#include <42parser/parser.h>
#include <42parser/ast.h>
#include <42parser/token.h>
#include <42parser/error.h>


/*
** Parse a command.
** Returns an error node on error.
*/
ast_t *parse_command(parser_t *parser)
{
    ast_t *node = ast_create(AT_COMMAND);
    ast_node_buffer_t *buffer = ast_node_buffer_create();
    bool has_arguments = false;
    ast_t *subnode;

    node->data = buffer;
    while (IS_COMMAND_NODE(parser->current->type)) {
        if (IS_ARGUMENT(parser->current->type))
            has_arguments = true;
        subnode = parse_subatom(parser);
        ast_node_buffer_append(buffer, subnode);
        if (subnode->type == AT_ERROR)
            return node;
    }
    if (!has_arguments)
        parser_errno_set(PE_NULL_COMMAND);
    return node;
}
