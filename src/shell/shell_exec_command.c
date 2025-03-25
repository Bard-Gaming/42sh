/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
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
** Wrapper around shell_subprocess to convert
** line buffer and env to compatible formats
** (i.e. a parsed command and a unix shell)
** in a memory-safe manner
*/
static pid_t call_command(char **args, sh_data_t *data)
{
    pid_t subprocess;
    char *cmd = shell_get_command_abs_path(args[0], data->env);

    subprocess = shell_subprocess(cmd, args, data);
    free(cmd);
    return subprocess;
}

/*
** Run the given builtin, but redirect
** stdin and stdout first (if necessary).
** This allows for piping with a builtin
** function.
*/
static int builtin_wrapper(builtin_cmd_t builtin, char **args, sh_data_t *data)
{
    int original_fds[2] = { dup(0), dup(1) };
    int exit_status;

    if (data->write_file != STDOUT_FILENO) {
        dup2(data->write_file, STDOUT_FILENO);
        close(data->write_file);
    }
    if (data->read_file != STDIN_FILENO) {
        dup2(data->read_file, STDIN_FILENO);
        close(data->read_file);
    }
    ;
    exit_status = builtin(args, data);
    ;
    dup2(original_fds[0], STDIN_FILENO);
    dup2(original_fds[1], STDOUT_FILENO);
    ;
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
    if (builtin != NULL)
        return builtin_wrapper(builtin, args, data);
    subprocess = call_command(args, data);
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
