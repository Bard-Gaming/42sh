/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_operation_pipe
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <42sh/io.h>
#include <42parser/ast.h>
#include <unistd.h>


/*
** Updates the read file.
** Note: This function only exists due
** to the coding-style's limitations, and
** I honestly wish I didn't have to do this.
*/
static void update_read_file(sh_data_t *data, int *pipefd)
{
    if (data->read_file > 0)
        close(data->read_file);
    data->read_file = pipefd[0];
}

/*
** Displays the message that should be
** displayed when a pipe fails.
*/
static void pipe_error(void)
{
    sh_puterr("Broken pipe.\n");
}

static void interpret_node(ast_t *node, sh_data_t *data)
{
    data->prev_subproc = -1;
    shell_interpret(node, data);
}

/*
** Execute the first command, then
** redirect everything it has written
** to stdout into the stdin of the
** second command.
*/
void shell_interpret_operation_pipe(ast_t *ast, sh_data_t *data)
{
    ast_node_buffer_t *nodes = ast->data;
    int parentfd[2] = { data->read_file, data->write_file };
    pid_t parent_subproc = data->prev_subproc;
    int pipefd[2];

    for (size_t i = 0; i < nodes->count - 1; i++) {
        if (pipe(pipefd) != 0)
            return pipe_error();
        data->write_file = pipefd[1];
        interpret_node(nodes->nodes[i], data);
        close(pipefd[1]);
        update_read_file(data, pipefd);
    }
    data->write_file = parentfd[1];
    data->prev_subproc = parent_subproc;
    shell_interpret(nodes->nodes[nodes->count - 1], data);
    close(data->read_file);
    data->read_file = parentfd[0];
}
