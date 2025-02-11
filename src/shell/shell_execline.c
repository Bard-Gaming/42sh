/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** shell_execline
*/

#include <mysh/shell.h>
#include <mysh/arguments.h>
#include <sys/wait.h>


/*
** Execute the command of a given line
** of arguments
*/
void shell_execline(char **line_buffer, char *env[])
{
    pid_t subproc = shell_subprocess(line_buffer[0], line_buffer, env);
    int status;

    waitpid(subproc, &status, 0);
}
