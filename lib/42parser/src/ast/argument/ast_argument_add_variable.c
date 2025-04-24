/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_argument_add_variable
*/

#include <42parser/ast.h>


/*
** Adds given variable name to the argument.
*/
void ast_argument_add_variable(ast_argument_t *arg, char *var)
{
    if (arg->length == arg->capacity)
        ast_argument_grow(arg);
    arg->data[arg->length].is_char = false;
    arg->data[arg->length].val.var = var;
    arg->length++;
}
