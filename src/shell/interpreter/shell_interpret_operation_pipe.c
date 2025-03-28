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
    int parentfd[2] = { data->read_file, data->write_file };
    int pipefd[2];
    ast_program_t *nodes = ast->data;

    for (size_t i = 0; i < nodes->count - 1; i++) {
        if (pipe(pipefd) != 0) {
            sh_puterr("Broken pipe.\n");
            return;
        }
        data->write_file = pipefd[1];
        shell_interpret(nodes->nodes[i], data);
        close(pipefd[1]);
        if (data->read_file > 0)
            close(data->read_file);
        data->read_file = pipefd[0];
    }
    data->write_file = parentfd[1];
    shell_interpret(nodes->nodes[nodes->count - 1], data);
    close(data->read_file);
    data->read_file = parentfd[0];
}
