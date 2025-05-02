/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_print_raw_argument
*/

#include <42parser/ast.h>
#include <stdio.h>


/*
** Prints a raw argument node.
*/
void ast_print_raw_argument(const ast_t *ast, unsigned short depth)
{
    ast_print_indent(depth + 1);
    printf("raw arg: \"%s\"\n", (const char *)ast->data);
}
