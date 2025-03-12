/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_operation_and
*/

#include <mysh/shell.h>
#include <mysh/data.h>
#include <42parser/ast.h>


/*
** Interpret the and (&&) operation
** between two commands.
** Executes the first command, then
** executes the second command if the
** first succeeded.
*/
void shell_interpret_operation_and(ast_t *ast, sh_data_t *data)
{
    ast_t **operands = ast->data;

    shell_interpret(operands[0], data);
    if (data->exit_status == 0)
        shell_interpret(operands[1], data);
}
