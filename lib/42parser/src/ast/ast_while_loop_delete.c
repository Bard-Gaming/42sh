/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_while_loop_delete
*/

#include <42parser/ast.h>
#include <stdlib.h>


/*
** Deletes a while loop statement
** data node.
*/
void ast_while_loop_delete(ast_while_loop_t *data)
{
    if (data->condition.is_command)
        ast_delete(data->condition.condition.command);
    else
        ast_node_buffer_delete(data->condition.condition.test_args);
    ast_delete(data->body);
    free(data);
}
