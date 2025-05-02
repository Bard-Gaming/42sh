/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_print
*/

#include <42parser/ast.h>
#include <stdio.h>


/*
** Recursively print an ast.
*/
void ast_print(const ast_t *ast)
{
    ast_print_node(ast, 0);
    putchar('\n');
}
