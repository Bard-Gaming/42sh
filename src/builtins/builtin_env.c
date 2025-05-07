/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** builtin_env
*/

#include <42sh/builtins.h>
#include <42sh/symbols.h>
#include <42sh/data.h>
#include <42sh/io.h>


/*
** Implementation for the shell's builtin
** env command.
** This command displays the shell's current
** environment by writing it to stdout in a
** specific format.
*/
int builtin_env(char *args[], sh_data_t *data)
{
    if (args[1] != NULL) {
        sh_puterr("env: Too many arguments.\n");
        return 1;
    }
    sh_symbols_print(data->env, "=");
    return 0;
}
