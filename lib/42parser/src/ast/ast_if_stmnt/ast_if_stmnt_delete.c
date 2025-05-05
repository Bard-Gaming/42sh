/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** ast_if_statement_delete
*/

#include <42parser/ast.h>
#include <stdlib.h>


/*
** Deletes an if statement's data, as well as
** all of the data allocated within.
*/
void ast_if_stmnt_delete(ast_if_stmnt_t *data)
{
    for (size_t i = 0; i < data->count; i++) {
        if (data->conditions[i].is_command)
            ast_delete(data->conditions[i].condition.command);
        else
            ast_node_buffer_delete(data->conditions[i].condition.test_args);
        ast_delete(data->bodies[i]);
    }
    ast_delete(data->bodies[data->count]);
    free(data->conditions);
    free(data->bodies);
    free(data);
}
