/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_print_argument
*/

#include <42parser/ast.h>
#include <stdio.h>


/*
** Prints an argument node.
*/
void ast_print_argument(const ast_t *ast, unsigned short depth)
{
    ast_argument_t *arg = ast->data;

    for (size_t i = 0; i < arg->length; i++) {
        if (arg->data[i].is_string) {
            ast_print_indent(depth + 1);
            printf("raw arg: \"%s\"\n", arg->data[i].val.str);
            continue;
        }
        ast_print_node(arg->data[i].val.node, depth);
    }
}
