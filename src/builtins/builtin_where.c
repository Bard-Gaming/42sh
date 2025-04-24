/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtin_where
*/

#include <42sh/builtins.h>
#include <42sh/shell.h>
#include <42sh/data.h>
#include <42sh/io.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void append_path(char ***results, char *dir, const char *command, int *count)
{
    char *full_path = NULL;

    asprintf(&full_path, "%s/%s", dir, command);
    if (access(full_path, X_OK) == 0) {
        (*results) = realloc((*results), sizeof(char *) * ((*count) + 2));
        (*results)[(*count)] = full_path;
        (*count)++;
        (*results)[(*count)] = NULL;
    } else {
        free(full_path);
    }
}

char **get_paths(const char *command, sh_data_t *data)
{
    char **results = NULL;
    const char *path_env = sh_data_getvar(data, "PATH");
    char *path_copy = NULL;
    char *dir = NULL;
    int count = 0;

    if (!path_env)
        return NULL;
    path_copy = strdup(path_env);
    dir = strtok(path_copy, ":");
    while (dir) {
        append_path(&results, dir, command, &count);
        dir = strtok(NULL, ":");
    }
    free(path_copy);
    return results;
}

void print_bin_path(char **paths)
{
    for (size_t i = 0; paths[i]; i++) {
        printf("%s\n", paths[i]);
        free(paths[i]);
    }
}

void print_command_info(const char *command, sh_data_t *data, int *status)
{
    char **paths;
    int builtin_or_alias = 0;

    if (sh_get_builtin(command)) {
        printf("%s is a shell built-in\n", command);
        builtin_or_alias = 1;
        *status = 0;
    }
    paths = get_paths(command, data);
    if ((!paths || !paths[0]) && !builtin_or_alias) {
        *status = 1;
    } else if ((paths && paths[0])) {
        print_bin_path(paths);
        free(paths);
        *status = 0;
    }
}

/*
** Error to display when not enough
** arguments are given.
*/
static int invalid_args_err(void)
{
    sh_puterr("where: Too few arguments.\n");
    return 1;
}

/*
** Implementation for the shell's builtin
** which command.
** This command tells the user what a given
** command is, i.e. if it is an alias, a shell
** builtin, or a binary specified in PATH.
*/
int builtin_where(char *args[], sh_data_t *data)
{
    int status = 0;

    if (args[1] == NULL)
        return invalid_args_err();
    for (int i = 1; args[i] != NULL; i++)
        print_command_info(args[i], data, &status);
    return status;
}
