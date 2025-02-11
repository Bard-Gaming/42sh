/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** shell_execline
*/

#include <mysh/shell.h>
#include <mysh/arguments.h>
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
** Execute the command of a given line
** of arguments
*/
int shell_execline(char **line_buffer, char *env[])
{
    pid_t subprocess;
    int status;
    char *cmd;
    builtin_cmd_t builtin;

    builtin = builtin_get(line_buffer[0]);
    if (builtin != NULL)
        return builtin((const char **)line_buffer, env);
    cmd = shell_parse_command(line_buffer[0], env);
    subprocess = shell_subprocess(cmd, line_buffer, env);
    free(cmd);
    waitpid(subprocess, &status, 0);
    if (WIFSIGNALED(status))
        return signal_error(status);
    return WEXITSTATUS(status);
}
