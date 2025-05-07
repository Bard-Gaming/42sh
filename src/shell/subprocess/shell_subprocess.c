/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_subprocess
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <42sh/builtins.h>
#include <42sh/io.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


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
** Function to return when the given program
** isn't found.
*/
static int invalid_program(const char *program)
{
    fprintf(stderr, "%s: Command not found.\n", program);
    return 1;
}

/*
** Executes an external program using the
** exec syscall.
*/
static int exec_program(char **args, sh_data_t *data)
{
    char *program = shell_get_command_abs_path(args[0], data);
    char **env;

    if (program == NULL)
        return invalid_program(args[0]);
    env = sh_env_create(data);
    execve(program, args, env);
    sh_cmd_perror(args[0]);
    sh_data_delete(data);
    sh_env_delete(env);
    free(program);
    return SH_EXEC_FAIL;
}

/*
** Creates a subprocess which runs the command
** specified by <args> (whether builtin or not),
** and retrieves the process' id.
** Returns -1 on error.
*/
pid_t shell_subprocess(char **args, sh_data_t *data)
{
    exec_fnc_t exec = sh_get_builtin(args[0]) ?: exec_program;
    pid_t subproc = fork();
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
