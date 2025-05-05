/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** ast_if_stmnt_add_command
*/

#include <42parser/ast.h>


/*
** Adds a condition command & body pair to the
** if statement.
*/
void ast_if_stmnt_add_command(ast_if_stmnt_t *data,
    ast_t *condition, ast_t *body)
{
    if (data->count + 1 >= data->capacity)
        ast_if_stmnt_grow(data);
    data->conditions[data->count].is_command = true;
    data->conditions[data->count].condition.command = condition;
    data->bodies[data->count] = body;
    data->count++;
    data->bodies[data->count] = NULL;
}
