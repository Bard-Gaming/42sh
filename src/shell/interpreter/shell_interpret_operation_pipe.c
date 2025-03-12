/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_operation_pipe
*/

#include <mysh/shell.h>
#include <mysh/data.h>
#include <mysh/io.h>
#include <42parser/ast.h>
#include <unistd.h>


/*
** Execute the first command, then
** redirect everything it has written
** to stdout into the stdin of the
** second command.
*/
void shell_interpret_operation_pipe(ast_t *ast, sh_data_t *data)
{
    ast_t **operands = ast->data;
    int stdout_duplicate = dup(data->io_files[STDOUT_FILENO]);
    int pipefd[2];

    if (pipe(pipefd) != 0) {
        sh_puterr("Broken pipe.\n");
        return;
    }
}
