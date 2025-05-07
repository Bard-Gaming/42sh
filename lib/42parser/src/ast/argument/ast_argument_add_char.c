/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_argument_add_char
*/

#include <42parser/ast.h>
#include <string.h>
#include <stdlib.h>


/*
** Creates a new component and allocates initial
** memory for a new string.
*/
static void add_new_component(ast_argument_t *arg, char c)
{
    size_t cap = AST_ARGUMENT_INIT_CAP;

    if (arg->length == arg->capacity)
        ast_argument_grow(arg);
    arg->data[arg->length].is_string = cap;
    arg->data[arg->length].val.str = malloc((cap + 1) * sizeof(char));
    arg->data[arg->length].val.str[0] = c;
    arg->data[arg->length].val.str[1] = '\0';
    arg->length++;
}

/*
** Adds a character to the given argument.
*/
void ast_argument_add_char(ast_argument_t *arg, char c)
{
    ast_arg_comp_t *comp = arg->data + arg->length - 1;
    size_t len;

    if (arg->length == 0 || !comp->is_string)
        return add_new_component(arg, c);
    len = strlen(comp->val.str);
    if (len + 1 >= comp->is_string) {
        comp->is_string *= 2;
        comp->val.str = realloc(comp->val.str,
            (comp->is_string + 1) * sizeof(char));
    }
    comp->val.str[len] = c;
    comp->val.str[len + 1] = '\0';
}
