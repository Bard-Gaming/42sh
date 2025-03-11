/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_input
*/

#include <mysh/shell.h>
#include <mysh/data.h>
#include <42parser/ast.h>


void shell_interpret_input(ast_t *ast, sh_data_t *data)
{
    ast_command_t *command = ast->data;

    if (ast->type == AT_COMMAND) {
        shell_exec_command(command->args, data);
    }
}
