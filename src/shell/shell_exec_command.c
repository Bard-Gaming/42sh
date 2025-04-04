/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_exec_command
*/

#include <mysh/shell.h>
#include <mysh/data.h>
#include <mysh/io.h>
#include <mysh/builtins.h>
#include <42parser/ast.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include <stdlib.h>
#include <unistd.h>


static int signal_error(int status)
{
    if (WTERMSIG(status) != SIGSEGV)
        return status;
    if (WCOREDUMP(status))
        sh_puterr("Segmentation fault (core dumped)\n");
    else
        sh_puterr("Segmentation fault\n");
    return status;
}

/*
** Execute the command specified
** by the given arguments.
*/
int shell_exec_command(char **args, sh_data_t *data)
{
    pid_t subprocess;
    int status;
    builtin_cmd_t builtin;

    builtin = builtin_get(args[0]);
    if (!IS_PIPE(data) && builtin != NULL)
        return builtin(args, data);
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
