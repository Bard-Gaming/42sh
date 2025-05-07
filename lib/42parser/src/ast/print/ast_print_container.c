/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_print_container
*/

#include <42parser/ast.h>


/*
** Prints all elements of a container node.
*/
void ast_print_container(const ast_t *ast, unsigned short depth)
{
    ast_node_buffer_t *buffer = ast->data;

    for (size_t i = 0; i < buffer->count; i++)
        ast_print_node(buffer->nodes[i], depth + 1);
}
