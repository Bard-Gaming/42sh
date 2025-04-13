/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_delete
*/

#include <42parser/ast.h>
#include <stdlib.h>


static const ast_delete_fnc_t delete_functions[AT_COUNT] = {
    [AT_ARGUMENT ... AT_FORMAT_STRING] = free,
    [AT_REDIRECT] = (ast_delete_fnc_t)ast_redirect_delete,
    [AT_COMMAND ... AT_COMPOUND] = (ast_delete_fnc_t)ast_node_buffer_delete,
    [AT_OPERATION_AND ... AT_OPERATION_OR] = ast_delete_binop_data,
    [AT_PIPELINE] = (ast_delete_fnc_t)ast_node_buffer_delete,
    [AT_PROGRAM] = (ast_delete_fnc_t)ast_node_buffer_delete,
};


/*
** Note:
** The function pointer variable has to be called "free".
** Failure to do so will generate a C-L6 error in the
** Coding Style Checker (for whatever reason).
*/
static void delete_data(ast_t *ast)
{
    ast_delete_fnc_t free = delete_functions[ast->type];

    if (free != NULL)
        free(ast->data);
}

/*
** Recursively delete the ast node
** and all of its children.
*/
void ast_delete(ast_t *ast)
{
    if (ast == NULL)
        return;
    delete_data(ast);
    free(ast);
}
