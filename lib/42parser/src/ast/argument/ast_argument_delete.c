/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_argument_delete
*/

#include <42parser/ast.h>
#include <stdlib.h>


/*
** Deletes an argument buffer
** and all of its allocated memory.
*/
void ast_argument_delete(ast_argument_t *arg)
{
    for (size_t i = 0; i < arg->length; i++) {
        if (arg->data[i].is_char)
            continue;
        ast_delete(arg->data[i].val.node);
    }
    free(arg->data);
    free(arg);
}
