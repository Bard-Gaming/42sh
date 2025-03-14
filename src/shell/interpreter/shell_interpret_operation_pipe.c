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


static void update_data_pipe(sh_data_t *data, const int *pipe)
{
    data->read_file = pipe[0];
    data->write_file = pipe[1];
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
    sh_command_state_t parent_state = data->cmd_state;
    ast_t **operands = ast->data;
    int pipefd[2];

    if (pipe(pipefd) != 0)
        return sh_puterr("Broken pipe.\n");
    ;
    data->cmd_state = parent_state | CS_PIPE_OUT;
    data->write_file = pipefd[1];
    shell_interpret(operands[0], data);
    close(pipefd[1]);
    ;
    data->cmd_state = parent_state | CS_PIPE_IN;
    update_data_pipe(data, parentfd);
    data->read_file = pipefd[0];
    shell_interpret(operands[1], data);
    close(pipefd[0]);
    ;
    data->cmd_state = CS_NORMAL;
}
