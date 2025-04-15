/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtin_which
*/


#include <42sh/builtins.h>
#include <42sh/shell.h>
#include <42sh/io.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/*
** Error to display when not enough
** arguments are given.
*/
static int invalid_args_err(void)
{
    sh_puterr("which: Too few arguments.\n");
    return 1;
}

/*
** Determines whether or not a given
** command is valid. The given command
*/
static bool is_valid_command(const char *command, const char *path)
{
    struct stat stat_buf;

    return
        strcmp(command, path) != 0 ||
        stat(command, &stat_buf) == 0;
}

/*
** Retrieves where the given command is,
** and prints the result.
** Returns true on success and false on
** error (i.e. if the given command doesn't
** exist).
** TODO: add check for aliases
*/
static bool print_command_info(const char *command, sh_data_t *data)
{
    bool success = true;
    char *absolute_path;

    if (builtin_get(command)) {
        printf("%s: shell built-in command.\n", command);
        return success;
    }
    absolute_path = shell_get_command_abs_path(command, data);
    if (!is_valid_command(command, absolute_path)) {
        printf("%s: Command not found.\n", command);
        success = false;
    } else {
        puts(absolute_path);
    }
    free(absolute_path);
    return success;
}

/*
** Implementation for the shell's builtin
** which command.
** This command tells the user what a given
** command is, i.e. if it is an alias, a shell
** builtin, or a binary specified in PATH.
*/
int builtin_which(char *args[], sh_data_t *data)
{
    int status = 0;

    if (args[1] == NULL)
        return invalid_args_err();
    for (int i = 1; args[i] != NULL; i++)
        if (!print_command_info(args[i], data))
            status = 1;
    return status;
}
