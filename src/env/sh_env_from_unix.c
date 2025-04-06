/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_env_from_unix
*/

#include <mysh/env.h>
#include <mysh/string.h>


/*
** Create a shell environment based on a
** unix-style environment. The given
** unix environment isn't modified.
*/
sh_env_t *sh_env_from_unix(const char **unix_env)
{
    sh_env_t *env = sh_env_create();

    if (env == NULL)
        return NULL;
    while (*unix_env != NULL) {
        sh_env_put(env, *unix_env);
        unix_env++;
    }
    return env;
}
