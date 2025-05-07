/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** builtin_cd
*/

#include <42sh/builtins.h>
#include <42sh/symbols.h>
#include <42sh/data.h>
#include <42sh/io.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


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
        return sh_data_getvar(data, "HOME");
    if (strcmp(raw_path, "-") == 0)
        return sh_data_getvar(data, "OLDPWD") ?: "";
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
        sh_symbols_set(data->env, "PWD", current_path);
    free(current_path);
    sh_symbols_set(data->env, "OLDPWD", prev_path);
    free(prev_path);
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
        return 2;
    }
    path = parse_dir_path(args[1], data);
    old_path = getcwd(NULL, 0);
    if (chdir(path) != 0) {
        sh_perror(path);
        free(old_path);
        return 1;
    }
    update_path(old_path, data);
    return 0;
}
