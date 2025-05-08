/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_foreach_loop_delete
*/

#include <42parser/ast.h>
#include <stdlib.h>


/*
** Deletes the data contained within
** a foreach loop node.
*/
void ast_foreach_loop_delete(ast_foreach_loop_t *loop)
{
    ast_delete(loop->variable);
    ast_node_buffer_delete(loop->list);
    ast_delete(loop->body);
    free(loop);
}
