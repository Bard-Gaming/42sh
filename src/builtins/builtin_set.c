/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtin_set
*/

#include <42sh/builtins.h>
#include <42sh/string.h>
#include <42sh/symbols.h>
#include <42sh/shell.h>
#include <42sh/data.h>
#include <42sh/io.h>
#include <stdlib.h>
#include <string.h>


static bool is_valid_name(const char *str)
{
    if (('0' <= *str && *str <= '9') || (*str == '=')) {
        sh_puterr("set: Variable name must begin with a letter.\n");
        return false;
    }
    return true;
}

int parse_set_arg(char **args[], sh_data_t *data)
{
    char *sep = strchr(**args, '=');

    if (sep) {
        *sep = '\0';
        sh_data_setvar(data, **args, sep + 1);
        (*args)++;
        return 0;
    }
    if (((*args)[1]) && strcmp(((*args)[1]), "=") == 0) {
        sh_data_setvar(data, (**args), (*args)[2] ?: "");
        (*args) += 3;
        return 0;
    } else {
        sh_data_setvar(data, (**args), "");
        (*args)++;
    }
    return 0;
}

int builtin_set(char *args[], sh_data_t *data)
{
    if (!args[1]) {
        sh_symbols_print(data->local_vars, "\t");
        return 0;
    }
    args++;
    while (*args) {
        if (!is_valid_name(*args)) {
            return 1;
        }
        parse_set_arg(&args, data);
    }
    return 0;
}
