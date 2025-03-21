/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_command
*/

#include <mysh/shell.h>
#include <mysh/data.h>
#include <mysh/io.h>
#include <42parser/ast.h>
#include <unistd.h>
#include <fcntl.h>


/*
** Works the same as dup2, with the exception
** that it opens a file descriptor based on the
** file path that is given.
** Returns true if successful, and false if not.
*/
static bool duplicate_path(ast_command_t *command, int io_file)
{
    int fd = open(
        command->io_files[io_file], command->open_flags[io_file], 0664
    );

    if (fd < 0) {
        sh_perror(command->io_files[io_file]);
        return false;
    }
    dup2(fd, io_file);
    close(fd);
    return true;
}

/*
** Interpret a command.
** Applies the necessary IO redirections,
** then executes the command.
*/
void shell_interpret_command(ast_t *ast, sh_data_t *data)
{
    int original_io[] = { dup(0), dup(1), dup(2) };
    ast_command_t *command = ast->data;
    intptr_t *command_fds = (void *)command->io_files;
    bool success = true;

    for (int io_file = 0; success && io_file < 3; io_file++) {
        if (!command->is_path[io_file])
            dup2(command_fds[io_file], io_file);
        else
            success = duplicate_path(command, io_file);
    }
    data->exit_status = success ? shell_exec_command(command->args, data) : 84;
    for (int io_file = 0; io_file < 3; io_file++) {
        dup2(original_io[io_file], io_file);
        close(original_io[io_file]);
    }
}
