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


void copy_pipe_in_data(int *pipefd, sh_data_t *data)
{
    data->pipe_read = pipefd[0];
    data->pipe_write = pipefd[1];
}

void transfer_contents(int src, int dest)
{
    char read_byte;
    ssize_t read_count = read(src, &read_byte, 1);

    while (read_count > 0) {
        write(dest, &read_byte, 1);
        read_count = read(src, &read_byte, 1);
    }
    close(dest);
}

/*
** Execute the first command, then
** redirect everything it has written
** to stdout into the stdin of the
** second command.
*/
void shell_interpret_operation_pipe(ast_t *ast, sh_data_t *data)
{
    ast_t **operands = ast->data;
    int pipefd[2];
    int parent_write_pipe = data->pipe_write;
    sh_command_state_t parent_state = data->cmd_state;

    if (pipe(pipefd) != 0) {
        sh_puterr("Broken pipe.\n");
        return;
    }
    data->cmd_state = CS_PIPE_OUT;
    copy_pipe_in_data(pipefd, data);
    shell_interpret(operands[0], data);
    close(data->pipe_write);
    copy_pipe_in_data(pipefd, data);
    data->cmd_state = CS_PIPE_IN;
    shell_interpret(operands[1], data);
    if (parent_state == CS_PIPE_OUT)
        transfer_contents(pipefd[0], parent_write_pipe);
    close(pipefd[0]);
    data->cmd_state = CS_NORMAL;
}
