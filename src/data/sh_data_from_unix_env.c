/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_data_from_unix_env
*/

#include <42sh/data.h>
#include <42sh/symbols.h>
#include <42sh/env.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


/*
** Updates the path stored in the
** SHELL environment variable to be
** the absolute path of the 42sh
** program.
*/
static void update_shell_path(sh_data_t *data)
{
    char shell_path[PATH_MAX];

    if (realpath("/proc/self/exe", shell_path) == NULL)
        return;
    sh_symbols_set(data->env_internal, "SHELL", shell_path);
}

/*
** Adds an environment variable to the
** shell's internal environment.
*/
static void add_env_var(sh_data_t *data, char *var)
{
    char *delim = strchr(var, '=');

    if (delim == NULL)
        return;
    *delim = '\0';
    sh_symbols_set(data->env_internal, var, delim + 1);
    *delim = '=';
}

/*
** Allocates a new shell data structure
** and fills its data with values from
** the given environment.
** The returned data structure should be
** deleted using the sh_data_delete()
** function.
** Returns NULL on error.
*/
sh_data_t *sh_data_from_unix_env(char *envp[])
{
    sh_data_t *data = sh_data_create();

    data->env_internal = sh_symbols_create();
    while (*envp != NULL) {
        add_env_var(data, *envp);
        envp++;
    }
    update_shell_path(data);
    data->local_vars = sh_symbols_create();
    data->env = sh_symbols_dup(data->env_internal);
    return data;
}
