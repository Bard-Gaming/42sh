/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_operation_or
*/

#include <mysh/shell.h>
#include <mysh/data.h>
#include <42parser/ast.h>


/*
** Interpret the or (||) operation
** between two commands.
** Executes the first command, then
** executes the second command if the
** first didn't succeed.
*/
void shell_interpret_operation_or(ast_t *ast, sh_data_t *data)
{
    ast_t **operands = ast->data;

    shell_interpret(operands[0], data);
    if (data->exit_status != 0)
        shell_interpret(operands[1], data);
}
