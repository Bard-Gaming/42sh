/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_subprocess
*/

#include <mysh/shell.h>
#include <mysh/data.h>
#include <mysh/builtins.h>
#include <mysh/io.h>
#include <unistd.h>
#include <stdlib.h>


/*
** Displays an error message and
** returns the appropriate error
** return value for when a fork
** fails.
*/
static pid_t fork_error(void)
{
    sh_puterr("Critical fork failure.\n");
    return -1;
}

/*
** Executes an external program using the
** exec syscall.
*/
static int exec_program(char **args, sh_data_t *data)
{
    char *program = shell_get_command_abs_path(args[0], data->env);
    char **env = sh_env_to_unix(data->env);

    execve(program, args, env);
    sh_cmd_perror(args[0]);
    sh_data_delete(data);
    sh_env_delete_unix(env);
    free(program);
    return SH_PROGRAM_ERR;
}

/*
** Creates a subprocess which runs the command
** specified by <args> (whether builtin or not),
** and retrieves the process' id.
** Returns -1 on error.
*/
pid_t shell_subprocess(char **args, sh_data_t *data)
{
    pid_t subproc = fork();
    exec_fnc_t exec = builtin_get(args[0]) ?: exec_program;
    int exit_status;

    if (subproc == -1)
        return fork_error();
    if (subproc != 0)
        return subproc;
    shell_setup_pipe(data);
    shell_setup_redirections(data);
    exit_status = exec(args, data);
    exit(exit_status);
}
