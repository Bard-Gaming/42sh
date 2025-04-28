/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_argument_add_node
*/

#include <42parser/ast.h>


/*
** Adds given node to a format argument.
*/
void ast_argument_add_node(ast_argument_t *arg, ast_t *node)
{
    if (arg->length == arg->capacity)
        ast_argument_grow(arg);
    arg->data[arg->length].is_char = false;
    arg->data[arg->length].val.node = node;
    arg->length++;
}
