/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** shell_execline
*/

#include <mysh/shell.h>
#include <mysh/arguments.h>
#include <mysh/data.h>
#include <mysh/io.h>
#include <mysh/builtins.h>
#include <sys/wait.h>
#include <sys/signal.h>


static int signal_error(int status)
{
    if (WTERMSIG(status) != SIGSEGV)
        return 84;
    if (WCOREDUMP(status))
        sh_puterr("Segmentation fault (core dumped)\n");
    else
        sh_puterr("Segmentation fault\n");
    return 84;
}

/*
** Wrapper around shell_subprocess to convert
** line buffer and env to compatible formats
** (i.e. a parsed command and a unix shell)
** in a memory-safe manner
*/
static pid_t call_command(char **line_buffer, sh_env_t *env)
{
    pid_t subprocess;
    char **unix_env = sh_env_to_unix(env);
    char *cmd = shell_get_command_abs_path(line_buffer[0], env);

    subprocess = shell_subprocess(cmd, line_buffer, unix_env);
    sh_env_delete_unix(unix_env);
    free(cmd);
    return subprocess;
}

/*
** Execute the command of a given line
** of arguments
*/
int shell_execline(char **line_buffer, sh_data_t *data)
{
    pid_t subprocess;
    int status;
    builtin_cmd_t builtin;

    builtin = builtin_get(line_buffer[0]);
    if (builtin != NULL)
        return builtin((const char **)line_buffer, data);
    subprocess = call_command(line_buffer, data->env);
    if (subprocess == -1)
        return 84;
    waitpid(subprocess, &status, 0);
    if (WIFSIGNALED(status))
        return signal_error(status);
    return WEXITSTATUS(status);
}
