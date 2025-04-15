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

//alias
int builtin_which(char *args[], sh_data_t *data)
{
    char *buff = NULL;
    char *bin = NULL;

    if (!args[1] || (!args[1] && !args[2])) {
        sh_puterr("repeat: Too few arguments.\n");
        return 1;
    }
    if (builtin_get(args[1])) {
        printf("%s: shell built-in command.\n", args[1]);
        return 0;
    }
    bin = shell_get_command_abs_path(args[1], data);
    if (strcmp(bin, args[1]) != 0) {
        printf("%s", bin);
    } else if (stat(args[1], buff)) {
        printf("%s", bin);
    } else {
        printf("%s: Command not found.\n", args[1]);
    }
    free(bin);
    return 0;
}