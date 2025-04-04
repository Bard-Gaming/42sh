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
** Opens a given file at path and saves the
** resulting file descriptor in the shell's
** data.
** Returns true on success and false on failure.
** If an error occurs, an error messages is printed
** to the error output, and the shell's data remains
** untouched.
*/
static bool open_file(const ast_command_t *command, int file, sh_data_t *data)
{
    int fd = open(command->io_files[file], command->open_flags[file], 0664);

    if (fd < 0) {
        sh_perror(command->io_files[file]);
        return false;
    }
    data->io_files[file] = fd;
    return true;
}

/*
** Set redirections up for use later on.
*/
static bool setup_redirections(const ast_command_t *command, sh_data_t *data)
{
    intptr_t *command_fds = (void *)command->io_files;
    bool success = true;

    for (int file = 0; success && file < 3; file++) {
        if (!command->is_path[file])
            data->io_files[file] = command_fds[file];
        else
            success = open_file(command, file, data);
    }
    return success;
}

/*
** Restore the original file descriptors
** for redirection, closing every file that
** was opened during the setup.
*/
static void cleanup_redirections(const ast_command_t *command, sh_data_t *data)
{
    for (int file = 0; file < 3; file++) {
        if (command->is_path[file] && data->io_files[file] != file)
            close(data->io_files[file]);
        data->io_files[file] = file;
    }
}

/*
** Interpret a command.
** Applies the necessary IO redirections,
** then executes the command.
**
** Note that the redirection cleanup has to
** be done even if the setup didn't succeed,
** since the setup may fail if one out of multiple
** files failed to open, meaning that the files
** that were successfully opened still need to be
** closed.
*/
void shell_interpret_command(ast_t *ast, sh_data_t *data)
{
    ast_command_t *command = ast->data;
    bool success;

    success = setup_redirections(command, data);
    data->exit_status = success ? shell_exec_command(command->args, data) : 84;
    cleanup_redirections(command, data);
}
