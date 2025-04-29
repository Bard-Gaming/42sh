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

    ast_delete(cond->condition);
    ast_delete(cond->body);
    free(cond);
}
