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
#include <sys/wait.h>
#include <sys/signal.h>


/*
** Execute the command of a given line
** of arguments
*/
void shell_execline(char **line_buffer, char *env[])
{
    pid_t subprocess;
    int status;
    char *cmd = shell_parse_command(line_buffer[0], env);

    subprocess = shell_subprocess(cmd, line_buffer, env);
    free(cmd);
    waitpid(subprocess, &status, 0);
    if (WTERMSIG(status) == SIGSEGV) {
        sh_puterr("Segmentation fault (core dumped)\n");
    }
}
