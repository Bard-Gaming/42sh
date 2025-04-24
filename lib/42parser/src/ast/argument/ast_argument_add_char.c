/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_argument_add_char
*/

#include <42parser/ast.h>


/*
** Adds a character to the given argument.
*/
void ast_argument_add_char(ast_argument_t *arg, char c)
{
    if (arg->length == arg->capacity)
        ast_argument_grow(arg);
    arg->data[arg->length].is_char = true;
    arg->data[arg->length].val.c = c;
    arg->length++;
}
