/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_if_stmnt_add
*/

#include <42parser/ast.h>


/*
** Adds a condition and body to
** the if statement's data.
*/
void ast_if_stmnt_add(ast_if_stmnt_t *data,
    ast_condition_t condition, ast_t *body)
{
    if (data->count + 1 >= data->capacity)
        ast_if_stmnt_grow(data);
    data->conditions[data->count] = condition;
    data->bodies[data->count] = body;
    data->count++;
    data->bodies[data->count] = NULL;
}
