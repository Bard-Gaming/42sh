/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_delete
*/

#include <42parser/ast.h>
#include <stdlib.h>


static void delete_data(ast_t *ast)
{
    static const ast_delete_fnc_t delete_fnc[AT_COUNT] = {
        [AT_COMMAND] = (ast_delete_fnc_t)ast_command_delete,
        [AT_PROGRAM] = (ast_delete_fnc_t)ast_program_delete,
        [AT_OPERATION_JOB... AT_OPERATION_OR] = ast_delete_binop_data,
    };

    if (delete_fnc[ast->type] != NULL)
        delete_fnc[ast->type](ast->data);
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
