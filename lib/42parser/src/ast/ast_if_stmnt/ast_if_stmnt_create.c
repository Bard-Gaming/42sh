/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_if_stmnt_create
*/

#include <42parser/ast.h>
#include <42parser/error.h>
#include <stdlib.h>


/*
** Creates an if statement data pointer.
*/
ast_if_stmnt_t *ast_if_stmnt_create(void)
{
    ast_if_stmnt_t *data = calloc(1, sizeof(ast_if_stmnt_t));

    if (data == NULL)
        parser_critical_error();
    return data;
}
