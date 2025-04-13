/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_node_buffer_delete
*/

#include <42parser/ast.h>
#include <stdlib.h>


/*
** Deletes an AST node buffer, as well
** as all of its containing data.
*/
void ast_node_buffer_delete(ast_node_buffer_t *buffer)
{
    for (size_t i = 0; i < buffer->count; i++)
        ast_delete(buffer->nodes[i]);
    free(buffer->nodes);
    free(buffer);
}
