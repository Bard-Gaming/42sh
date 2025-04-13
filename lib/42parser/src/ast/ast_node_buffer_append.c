/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_node_buffer_append
*/

#include <42parser/ast.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


/*
** Grows a buffer's internal data buffer
** by AST_BUFFER_GROWTH_FACTOR.
*/
static bool grow_buffer(ast_node_buffer_t *buffer)
{
    buffer->capacity *= AST_BUFFER_GROWTH_FACTOR;
    buffer->nodes = reallocarray(
        buffer->nodes,
        buffer->capacity,
        sizeof(ast_t *)
    );
    return buffer->nodes != NULL;
}

/*
** Appends a node to the given node buffer.
** Does nothing on error.
*/
void ast_node_buffer_append(ast_node_buffer_t *buffer, ast_t *node)
{
    if (buffer->count == buffer->capacity) {
        if (!grow_buffer(buffer)) {
            fputs("42parser: warning: Insufficient memory\n", stderr);
            return;
        }
    }
    buffer->nodes[buffer->count] = node;
    buffer->count++;
}
