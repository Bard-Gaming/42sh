/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_print_variable
*/

#include <42parser/ast.h>
#include <stdio.h>


/*
** Prints a variable node.
*/
void ast_print_variable(const ast_t *ast, unsigned short depth)
{
    ast_print_indent(depth + 1);
    printf("\"%s\"\n", (const char *)ast->data);
}
