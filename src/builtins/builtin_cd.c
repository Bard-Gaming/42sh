/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** builtin_cd
*/

#include <mysh/builtins.h>
#include <mysh/data.h>
#include <mysh/env.h>
#include <mysh/string.h>
#include <mysh/io.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


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
** the get_home_path() function, except
** that is handles the OLDPWD path instead
** of the HOME path.
*/
static const char *get_prev_path(const sh_data_t *data)
{
    const char *prev_path = data->previous_dir;

    if (prev_path == NULL)
        prev_path = sh_env_get(data->env, "OLDPWD");
    return prev_path == NULL ? "" : prev_path;
}

/*
** Parses a directory path.
** If the given directory is not NULL
** and not '-', the given path is left
** unchanged.
** Note that the result of this function
** should never be freed/modified.
*/
static const char *parse_dir_path(const char *raw_path, sh_data_t *data)
{
    if (raw_path == NULL)
        return get_home_path(data);
    if (sh_strcmp(raw_path, "-") == 0)
        return get_prev_path(data);
    return raw_path;
}

/*
** Updates the path in the shell's environment.
** This includes both the current path (PWD),
** as well as the old path (OLDPWD).
** This, however, does not change
** the current work directory.
*/
static void update_path(char *prev_path, sh_data_t *data)
{
    char *current_path = getcwd(NULL, 0);

    if (current_path != NULL)
        sh_env_set(data->env, "PWD", current_path);
    free(current_path);
    free(data->previous_dir);
    data->previous_dir = prev_path;
    sh_env_set(data->env, "OLDPWD", prev_path);
}

/*
** Implementation for the shell's builtin
** cd command.
** This command allows the user to change
** into any (valid) directory of their
** choosing.
*/
int builtin_cd(char *args[], sh_data_t *data)
{
    const char *path;
    char *old_path;

    if (args[1] != NULL && args[2] != NULL) {
        sh_puterr("cd: Too many arguments.\n");
        return 84;
    }
    path = parse_dir_path(args[1], data);
    old_path = getcwd(NULL, 0);
    if (chdir(path) != 0) {
        sh_perror(path);
        free(old_path);
        return 84;
    }
    update_path(old_path, data);
    return 0;
}
