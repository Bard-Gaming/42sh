/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_exec_command
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <42sh/io.h>
#include <42sh/builtins.h>
#include <42parser/ast.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include <stdlib.h>
#include <unistd.h>


/*
** Displays the appropriate error
** message and returns the exit
** status for the given signal.
*/
static int signal_error(int status)
{
    switch (WTERMSIG(status)) {
    case SIGSEGV:
        sh_puterr("Segmentation fault");
        break;
    case SIGFPE:
        sh_puterr("Floating point exception");
        break;
    default:
        break;
    }
    sh_puterr(WCOREDUMP(status) ? " (core dumped)\n" : "\n");
    return status;
}

/*
** Builtin wrapper that applies all
** redirections, executes the builtin,
** and restore the original io files
** to stdin, stdout, and stderr
** respectively.
*/
static int builtin_redirect(builtin_cmd_t fnc, char **args, sh_data_t *data)
{
    int original_fds[3] = { dup(0), dup(1), dup(2) };
    int exit_status;

    for (int file = 0; file < 3; file++)
        dup2(data->io_files[file], file);
    exit_status = fnc(args, data);
    for (int file = 0; file < 3; file++) {
        dup2(original_fds[file], file);
        close(original_fds[file]);
    }
    return exit_status;
}

/*
** Execute the command specified
** by the given argument buffer.
*/
int shell_exec_command(char **args, sh_data_t *data)
{
    pid_t subprocess;
    int status;
    builtin_cmd_t builtin;

    builtin = builtin_get(args[0]);
    if (!IS_PIPE(data) && builtin != NULL)
        return builtin_redirect(builtin, args, data);
    subprocess = shell_subprocess(args, data);
    if (subprocess == -1)
        return 84;
    if (data->write_file != 1) {
        data->prev_subproc = subprocess;
        return -1;
    }
    waitpid(subprocess, &status, 0);
    if (WIFSIGNALED(status))
        return signal_error(status);
    return WEXITSTATUS(status);
}
