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


static void update_data_pipe(sh_data_t *data, int pipe_in, int pipe_out)
{
    data->read_file = pipe_in;
    data->write_file = pipe_out;
}

/*
** Execute the first command, then
** redirect everything it has written
** to stdout into the stdin of the
** second command.
*/
void shell_interpret_operation_pipe(ast_t *ast, sh_data_t *data)
{
    int parentfd[2] = { data->read_file, data->write_file };
    ast_t **operands = ast->data;
    int pipefd[2];

    if (pipe(pipefd) != 0) {
        sh_puterr("Broken pipe.\n");
        return;
    }
    ;
    update_data_pipe(data, parentfd[0], pipefd[1]);
    shell_interpret(operands[0], data);
    close(pipefd[1]);
    ;
    update_data_pipe(data, pipefd[0], parentfd[1]);
    shell_interpret(operands[1], data);
    close(pipefd[0]);
}
