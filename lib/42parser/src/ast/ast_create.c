/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_create
*/

#include <42parser/ast.h>
#include <stdlib.h>


/*
** Create a new ast node of the given
** type. Returns NULL on error.
*/
ast_t *ast_create(ast_type_t type)
{
    ast_t *node = malloc(sizeof(ast_t));

    if (node == NULL)
        return NULL;
    node->type = type;
    node->data = NULL;
    return node;
}
