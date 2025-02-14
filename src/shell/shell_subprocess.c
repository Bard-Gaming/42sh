/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** shell_subprocess
*/

#include <mysh/shell.h>
#include <mysh/io.h>
#include <mysh/arguments.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


pid_t fork_error(void)
{
    sh_puterr("mysh: critical error: failed to fork\n");
    return -1;
}

/*
** Create a subprocess with given args
** and get its process id.
** TODO: add error handling (subproc == -1)
*/
pid_t shell_subprocess(const char *program, char **args, char *env[])
{
    pid_t subproc = fork();

    if (subproc == -1)
        return fork_error();
    if (subproc != 0)
        return subproc;
    execve(program, args, env);
    sh_puterr(args[0]);
    sh_puterr(": command not found.\n");
    exit(84);
}
