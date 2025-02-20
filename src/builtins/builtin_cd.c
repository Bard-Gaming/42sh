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
    return sh_strcmp(value, "~") == 0;
}

/*
** Returns the abolute path of the user's
** home directory. The home directory is
** stored internally, but if not present,
** this function gets the value of the
** HOME env var.
** If the home path hasn't been saved
** internally AND the HOME env var isn't
** set, "/" is returned instead.
** If the home path hasn't been saved
** internally but the HOME env var IS set,
** then the directory from the env var is
** saved internally.
*/
static const char *get_home_path(sh_data_t *data)
{
    const char *path = data->home_dir;

    if (path == NULL) {
        path = sh_env_get(data->env, "HOME");
        if (path != NULL)
            data->home_dir = sh_strdup(path);
    }
    return path == NULL ? "/" : path;
}

/*
** This function mostly behaves like
** the get_home_path() function
*/
static const char *get_prev_path(const char *current_path, sh_data_t *data)
{
    const char *prev_path = data->previous_dir;

    if (prev_path == NULL)
        prev_path = sh_env_get(data->env, "OLDPWD");
    return prev_path == NULL ? current_path : prev_path;
}

static const char *parse_dir_path(const char *raw_path, sh_data_t *data)
{
    if (is_home_alias(raw_path))
        return get_home_path(data);
    if (sh_strcmp(raw_path, "-") == 0)
        return get_prev_path(raw_path, data);
    return raw_path;
}

static void update_previous_path(char *prev_path, sh_data_t *data)
{
    data->previous_dir = prev_path;
    sh_env_set(data->env, "OLDPWD", prev_path);
}

static int path_not_found_err(const char *path, char *prev_path)
{
    sh_puterr(path);
    sh_puterr(": No such file or directory.\n");
    free(prev_path);
    return 84;
}

int builtin_cd(const char *args[], sh_data_t *data)
{
    const char *path;
    char *old_path;

    if (args[1] != NULL && args[2] != NULL) {
        sh_puterr("cd: Too many arguments.\n");
        return 84;
    }
    path = parse_dir_path(args[1], data);
    old_path = getcwd(NULL, 0);
    if (chdir(path) != 0)
        return path_not_found_err(path, old_path);
    update_previous_path(old_path, data);
    return 0;
}
