/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtin_unset
*/

#include <42sh/builtins.h>
#include <42sh/string.h>
#include <42sh/symbols.h>
#include <42sh/shell.h>
#include <42sh/data.h>
#include <42sh/io.h>
#include <stdlib.h>
#include <string.h>

int builtin_unset(char *args[], sh_data_t *data)
{
    if (args[1] == NULL) {
        sh_puterr("unset: Too few arguments.\n");
        return 1;
    }
    args++;
    while (*args != NULL) {
        sh_symbols_unset(data->local_vars, *args);
        args++;
    }
    return 0;
}
