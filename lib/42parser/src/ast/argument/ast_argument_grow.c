/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_argument_grow
*/

#include <42parser/ast.h>
#include <stdlib.h>


/*
** Grows the argument buffer's capacity.
*/
void ast_argument_grow(ast_argument_t *arg)
{
    arg->capacity = arg->capacity == 0 ?
        AST_ARGUMENT_INIT_CAP : arg->capacity * AST_BUFFER_GROWTH_FACTOR;
    arg->data = reallocarray(arg->data, arg->capacity, sizeof(ast_arg_comp_t));
}
