/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** builtin_cd
*/

#include <mysh/builtins.h>
#include <mysh/string.h>
#include <mysh/io.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>


static const char *get_home_dir(sh_env_t *env)
{
    const char *dir = sh_env_get(env, "HOME");

    return dir == NULL ? "/" : dir;
}

static bool is_home_alias(const char *value)
{
    if (value == NULL)
        return true;
    return value[0] == '~' && value[1] == '\0';
}

int builtin_cd(const char *args[], sh_env_t *env)
{
    struct stat stat_buf;
    const char *path;

    if (args[1] != NULL && args[2] != NULL) {
        sh_puterr("cd: Too many arguments.\n");
        return 84;
    }
    path = is_home_alias(args[1]) ? get_home_dir(env) : args[1];
    if (stat(path, &stat_buf) != 0) {
        sh_puterr(path);
        sh_puterr(": No such file or directory.\n");
        return 84;
    }
    chdir(path);
    return 0;
}
