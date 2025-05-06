/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** builtin_setenv
*/

#include <42sh/builtins.h>
#include <42sh/string.h>
#include <42sh/data.h>
#include <42sh/io.h>
#include <stdbool.h>


/*
** Implementation for the shell's builtin
** setenv command.
** This command changes or adds environment
** variables to the shell's environment.
** If no arguments are given, the command behaves
** exactly like env would.
*/
int builtin_setenv(char *args[], sh_data_t *data)
{
    if (args[1] == NULL)
        return builtin_env(args, data);
    if (args[2] != NULL && args[3] != NULL) {
        sh_puterr("setenv: Too many arguments.\n");
        return 1;
    }
    if (!sh_strisname(args[1], "setenv"))
        return 1;
    sh_data_setenv(data, args[1], args[2] == NULL ? "" : args[2]);
    return 0;
}
