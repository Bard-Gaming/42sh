/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_node_buffer_create
*/

#include <42parser/ast.h>
#include <stdlib.h>


/*
** Allocate the necessary memory to store
** a new node buffer, and initializes it to
** its default values.
** Returns NULL on error.
*/
ast_node_buffer_t *ast_node_buffer_create(void)
{
    ast_node_buffer_t *buffer = malloc(sizeof(ast_node_buffer_t));

    if (buffer == NULL)
        return NULL;
    buffer->count = 0;
    buffer->capacity = AST_BUFFER_INIT_CAP;
    buffer->nodes = malloc(buffer->capacity * sizeof(ast_t *));
    if (buffer->nodes == NULL) {
        free(buffer);
        return NULL;
    }
    return buffer;
}
