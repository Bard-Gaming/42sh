/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** builtin_exec
*/

#include <42sh/builtins.h>
#include <42sh/string.h>
#include <42sh/shell.h>
#include <42sh/data.h>
#include <42sh/env.h>
#include <42sh/io.h>
#include <unistd.h>
#include <stdlib.h>


/*
** Prints the exec error message
** in the correct format.
*/
static void exec_err(const char *prog)
{
    char *prefix = sh_strjoin("exec: ", prog);

    sh_cmd_perror(prefix);
    free(prefix);
}

/*
** Implementation for the shell's builtin
** exec command.
** This command allows the user to replace
** the shell's process image with the given
** command.
*/
int builtin_exec(char *args[], sh_data_t *data)
{
    char **unix_env;
    char *prog_path;

    if (args[1] == NULL)
        return 0;
    unix_env = sh_env_to_unix(data->env);
    prog_path = shell_get_command_abs_path(args[1], data->env);
    execve(prog_path, args + 1, unix_env);
    sh_env_delete_unix(unix_env);
    exec_err(args[1]);
    free(prog_path);
    return 127;
}
