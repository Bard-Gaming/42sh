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


static pid_t fork_error(void)
{
    sh_puterr("mysh: critical error: failed to fork\n");
    return -1;
}

/*
** Set io files up for redirection.
*/
static void initialize_redirection(sh_data_t *data)
{
    if (data->read_file != 0) {
        dup2(data->read_file, 0);
        close(data->read_file);
    }
    if (data->write_file != 1) {
        dup2(data->write_file, 1);
        close(data->write_file);
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
    initialize_redirection(data);
    env = sh_env_to_unix(data->env);
    execve(program, args, env);
    sh_cmd_perror(args[0]);
    sh_env_delete_unix(env);
    exit(127);
}
