/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_data_from_unix_env
*/

#include <mysh/data.h>
#include <mysh/env.h>
#include <mysh/string.h>
#include <unistd.h>


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
    data->home_dir = buffer == NULL ? NULL : sh_strdup(buffer);
    buffer = sh_env_get(env, "OLDPWD");
    data->previous_dir = sh_strdup(buffer == NULL ? "" : buffer);
    return data;
}
