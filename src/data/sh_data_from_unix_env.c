/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_data_from_unix_env
*/

#include <42sh/data.h>
#include <42sh/symbols.h>
#include <42sh/string.h>
#include <unistd.h>
#include <pwd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>


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
    data->shell_path = sh_strdup(shell_path);
}

/*
** Updates the internal environment's
** data to store all kinds of user-
** related data, in case any of it is
** missing.
*/
static void update_user_data(sh_symbols_t *env)
{
    uid_t uid = geteuid();
    struct passwd *data = getpwuid(uid);

    if (sh_symbols_get(env, "USER") == NULL)
        sh_symbols_set(env, "USER", data->pw_name);
    if (sh_symbols_get(env, "HOME") == NULL)
        sh_symbols_set(env, "HOME", data->pw_dir);
    if (sh_symbols_get(env, "SHELL") == NULL)
        sh_symbols_set(env, "SHELL", data->pw_shell);
}

/*
** Sets default values for the given environment.
** The shell relies on these defaults being set
** for the internal environment, so this is a critical
** step.
*/
static void set_defaults(sh_data_t *data)
{
    update_shell_path(data);
    update_user_data(data->env_internal);
    if (sh_symbols_get(data->env_internal, "PS1") == NULL)
        sh_symbols_set(data->env_internal, "PS1", SHELL_PROMPT);
    if (sh_symbols_get(data->env_internal, "PATH") == NULL)
        sh_symbols_set(data->env_internal, "PATH", "/usr/bin:/bin");
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
    set_defaults(data);
    data->aliases = sh_symbols_create();
    data->local_vars = sh_symbols_create();
    data->env = sh_symbols_dup(data->env_internal);
    return data;
}
