/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_print_binary_operation
*/

#include <42parser/ast.h>


/*
** Prints the nodes of a binary operation.
*/
void ast_print_binary_operation(const ast_t *ast, unsigned short depth)
{
    ast_t **data = ast->data;

    ast_print_node(data[0], depth + 1);
    ast_print_node(data[1], depth + 1);
}
