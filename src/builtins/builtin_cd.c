/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** builtin_cd
*/

#include <mysh/builtins.h>
#include <mysh/data.h>
#include <mysh/env.h>
#include <mysh/string.h>
#include <mysh/io.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>


static bool is_home_alias(const char *value)
{
    if (value == NULL)
        return true;
    return value[0] == '~' && value[1] == '\0';
}

static const char *parse_dir_path(const char *raw_path, sh_env_t *env)
{
    const char *dir;

    if (is_home_alias(raw_path)) {
        dir = sh_env_get(env, "HOME");
        return dir == NULL ? "/" : dir;
    }
    if (raw_path[0] == '-' && raw_path[1] == '\0') {
        dir = sh_env_get(env, "OLDPWD");
        return dir == NULL ? "" : dir;
    }
    return raw_path;
}

int builtin_cd(const char *args[], sh_data_t *data)
{
    const char *path;
    char *old_path;

    if (args[1] != NULL && args[2] != NULL) {
        sh_puterr("cd: Too many arguments.\n");
        return 84;
    }
    path = parse_dir_path(args[1], data->env);
    old_path = getcwd(NULL, 0);
    if (chdir(path) != 0) {
        sh_puterr(path);
        sh_puterr(": No such file or directory.\n");
        free(old_path);
        return 84;
    }
    sh_env_set(data->env, "OLDPWD", old_path);
    free(old_path);
    return 0;
}
