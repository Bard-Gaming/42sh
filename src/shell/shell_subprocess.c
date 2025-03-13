/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** shell_subprocess
*/

#include <mysh/shell.h>
#include <mysh/data.h>
#include <mysh/io.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


pid_t fork_error(void)
{
    sh_puterr("mysh: critical error: failed to fork\n");
    return -1;
}

/*
** Initiate the redirection
*/
void init_redirect(sh_data_t *data)
{
    switch (data->cmd_state) {
    case CS_PIPE_IN:
        close(data->pipe_write);
        dup2(data->pipe_read, STDIN_FILENO);
        close(data->pipe_read);
        return;
    case CS_PIPE_OUT:
        close(data->pipe_read);
        dup2(data->pipe_write, STDOUT_FILENO);
        close(data->pipe_write);
        return;
    default:
        return;
    }
}

/*
** Create a subprocess with given args
** and get its process id.
*/
pid_t shell_subprocess(const char *program, char **args, sh_data_t *data)
{
    pid_t subproc = fork();
    char **env;

    if (subproc == -1)
        return fork_error();
    if (subproc != 0)
        return subproc;
    if (data->cmd_state != CS_NORMAL)
        init_redirect(data);
    env = sh_env_to_unix(data->env);
    execve(program, args, env);
    sh_cmd_perror(args[0]);
    sh_env_delete_unix(env);
    exit(84);
}
