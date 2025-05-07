/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_while_stmnt_delete
*/

#include <42parser/ast.h>
#include <stdlib.h>


/*
** Deletes a while statement data
** node.
*/
void ast_while_stmnt_delete(ast_while_stmnt_t *data)
{
    if (data->condition.is_command)
        ast_delete(data->condition.condition.command);
    else
        ast_node_buffer_delete(data->condition.condition.test_args);
    ast_delete(data->body);
    free(data);
}
