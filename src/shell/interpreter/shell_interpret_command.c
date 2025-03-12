/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_command
*/

#include <mysh/shell.h>
#include <mysh/data.h>
#include <42parser/ast.h>


/*
** Interpret a command.
** All this does is executing the
** given command.
** Not much more to it, is there?
*/
void shell_interpret_command(ast_t *ast, sh_data_t *data)
{
    ast_command_t *command = ast->data;

    data->exit_status = shell_exec_command(command->args, data);
}
