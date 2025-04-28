/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_command
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <42sh/vector.h>
#include <unistd.h>
#include <stdlib.h>


/*
** Sets up the necessary io redirections and
** argument vector, which are required to
** properly run the command.
*/
static bool setup(ast_node_buffer_t *cmd, sh_data_t *data, sh_vector_t *argv)
{
    sh_vector_t *current_arg;

    data->exit_status = 0;
    for (size_t i = 0; i < cmd->count; i++) {
        current_arg = shell_interpret(cmd->nodes[i], data);
        if (data->exit_status != 0)
            return false;
        if (current_arg == NULL)
            continue;
        sh_vector_append_range(argv, current_arg);
        sh_vector_delete(current_arg, NULL);
        free(current_arg);
    }
    return true;
}

/*
** Cleans up io redirections, as well
** as the given argument vector.
*/
static void cleanup(sh_data_t *data, sh_vector_t *argv)
{
    for (int file = 0; file < 3; file++) {
        if (data->should_close[file])
            close(data->io_files[file]);
        data->should_close[file] = false;
        data->io_files[file] = file;
    }
    sh_vector_delete(argv, NULL);
}

/*
** Interpret a command.
** Applies the necessary IO redirections,
** interprets the all of the command's
** arguments, then executes the given command.
*/
void shell_interpret_command(ast_t *ast, sh_data_t *data)
{
    sh_vector_t argv = { 0 };

    if (!setup(ast->data, data, &argv))
        return;
    data->exit_status = shell_exec_command((char **)argv.data, data);
    cleanup(data, &argv);
}
