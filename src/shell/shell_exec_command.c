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
static pid_t call_command(char **args, sh_env_t *env)
{
    pid_t subprocess;
    char **unix_env = sh_env_to_unix(env);
    char *cmd = shell_get_command_abs_path(args[0], env);

    subprocess = shell_subprocess(cmd, args, unix_env);
    sh_env_delete_unix(unix_env);
    free(cmd);
    return subprocess;
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
        return builtin(args, data);
    subprocess = call_command(args, data->env);
    if (subprocess == -1)
        return 84;
    waitpid(subprocess, &status, 0);
    if (WIFSIGNALED(status))
        return signal_error(status);
    return WEXITSTATUS(status);
}
