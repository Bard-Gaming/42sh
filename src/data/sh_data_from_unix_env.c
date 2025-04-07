/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_data_from_unix_env
*/

#include <42sh/data.h>
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
static void update_shell_path(sh_env_t *env)
{
    char shell_path[PATH_MAX];

    if (realpath("/proc/self/exe", shell_path) == NULL)
        return;
    sh_env_set(env, "SHELL", shell_path);
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
    sh_env_t *env;
    const char *buffer;

    if (data == NULL)
        return NULL;
    env = sh_env_from_unix((const char **)envp);
    if (env == NULL) {
        free(data);
        return NULL;
    }
    data->env = env;
    buffer = sh_env_get(env, "HOME");
    data->home_dir = buffer == NULL ? NULL : strdup(buffer);
    buffer = sh_env_get(env, "OLDPWD");
    data->previous_dir = strdup(buffer == NULL ? "" : buffer);
    update_shell_path(env);
    return data;
}
