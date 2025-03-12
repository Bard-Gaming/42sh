/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_command_chain
*/

#include <mysh/shell.h>
#include <mysh/data.h>
#include <42parser/ast.h>


/*
** Interpret a chain of commands.
** A chain of commands is simply two
** commands separated by a semicolon.
*/
void shell_interpret_command_chain(ast_t *ast, sh_data_t *data)
{
    ast_t **operands = ast->data;

    shell_interpret(operands[0], data);
    shell_interpret(operands[1], data);
}
