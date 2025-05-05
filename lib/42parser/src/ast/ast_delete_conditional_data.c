/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_delete_conditional_data
*/

#include <42parser/ast.h>
#include <stdlib.h>


void ast_delete_conditional_data(void *data)
{
    ast_conditional_t *cond = data;

    if (cond->is_command)
        ast_delete(cond->condition.command);
    else
        ast_node_buffer_delete(cond->condition.test_args);
    ast_delete(cond->body);
    free(cond);
}
