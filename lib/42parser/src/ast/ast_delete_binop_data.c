/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_delete_binop_data
*/

#include <42parser/ast.h>
#include <stdlib.h>


/*
** Delete an operation node's data.
*/
void ast_delete_binop_data(void *data)
{
    ast_t **binop_data = data;

    ast_delete(binop_data[0]);
    ast_delete(binop_data[1]);
    free(binop_data);
}
