/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_if_statement_add
*/

#include <42parser/ast.h>
#include <42parser/error.h>
#include <stdlib.h>


/*
** Adds a test condition & duo pair to the if
** statement.
*/
void ast_if_stmnt_grow(ast_if_stmnt_t *data)
{
    data->capacity = data->capacity == 0 ?
        AST_BUFFER_INIT_CAP : data->capacity * 2;
    data->bodies = reallocarray(
        data->bodies, data->capacity, sizeof(ast_t *)
    );
    data->conditions = reallocarray(
        data->conditions, data->capacity, sizeof(ast_condition_t *)
    );
    if (data->bodies == NULL || data->conditions == NULL)
        parser_critical_error();
}
