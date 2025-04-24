/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtin_where
*/

#include <42sh/builtins.h>
#include <42sh/vector.h>
#include <42sh/shell.h>
#include <42sh/data.h>
#include <42sh/io.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/*
** Constructs a path string composed
** of the given directory and the given
** command.
** If the resulting path does not point
** to a valid file, NULL is returned
** instead.
*/
static char *get_path(const char *dir, const char *command)
{
    char *full_path = NULL;

    (void)!asprintf(&full_path, "%s/%s", dir, command);
    if (access(full_path, X_OK) == 0)
        return full_path;
    free(full_path);
    return NULL;
}

/*
** Updates the given path vector with
** all valid paths to the given command.
*/
static void update_path_vector(sh_vector_t *paths,
    const char *command, sh_data_t *data)
{
    char *path_env = strdup(sh_data_getvar(data, "PATH"));
    char *dir = strtok(path_env, ":");
    char *path;

    while (dir != NULL) {
        path = get_path(dir, command);
        if (path != NULL)
            sh_vector_push_back(paths, path);
        dir = strtok(NULL, ":");
    }
    free(path_env);
}

/*
** Prints all paths in the given path
** vector.
*/
static void print_paths(const sh_vector_t *paths)
{
    for (size_t i = 0; i < paths->count; i++)
        puts(paths->data[i]);
}

/*
** Prints the location of any given command
** (if possible).
** Returns true on success and false on error.
*/
static bool print_command_info(const char *command, sh_data_t *data)
{
    sh_vector_t paths = { 0 };
    char *builtin_str;
    bool success;

    if (sh_get_builtin(command)) {
        (void)!asprintf(&builtin_str, "%s is a shell built-in", command);
        sh_vector_push_back(&paths, builtin_str);
    }
    update_path_vector(&paths, command, data);
    print_paths(&paths);
    success = paths.count != 0;
    sh_vector_delete(&paths, NULL);
    return success;
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
** where command.
** This command tells the user all the locations
** of where a given command's binary is.
*/
int builtin_where(char *args[], sh_data_t *data)
{
    int status = 0;

    if (args[1] == NULL)
        return invalid_args_err();
    for (size_t i = 1; args[i] != NULL; i++)
        if (!print_command_info(args[i], data))
            status = 1;
    return status;
}
