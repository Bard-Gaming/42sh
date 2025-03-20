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
** Set everything up for redirection.
** This function should only ever be
** called when the given cmd_state
** is not NORMAL, as closing the pipes
** is otherwise unsafe.
*/
static void initialize_redirection(sh_data_t *data)
{
    if (IS_PIPE_IN(data->cmd_state)) {
        dup2(data->read_file, STDIN_FILENO);
        close(data->read_file);
    }
    if (IS_PIPE_OUT(data->cmd_state)) {
        dup2(data->write_file, STDOUT_FILENO);
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
    if (data->cmd_state != CS_NORMAL)
        initialize_redirection(data);
    env = sh_env_to_unix(data->env);
    execve(program, args, env);
    sh_cmd_perror(args[0]);
    sh_env_delete_unix(env);
    exit(84);
}
