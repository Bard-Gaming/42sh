/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** builtin_set
*/

#include <42sh/builtins.h>
#include <42sh/symbols.h>
#include <42sh/string.h>
#include <42sh/data.h>
#include <string.h>


/*
** Parses a single set of arguments
** (corresponds to setting a single variable).
*/
static void parse_set_arg(char **args[], sh_data_t *data)
{
    char *sep = strchr(**args, '=');

    if (sep) {
        *sep = '\0';
        sh_data_setvar(data, **args, sep + 1);
        (*args)++;
        return;
    }
    if ((*args)[1] && strcmp((*args)[1], "=") == 0) {
        sh_data_setvar(data, (**args), (*args)[2] ?: "");
        (*args) += 3;
        return;
    }
    sh_data_setvar(data, (**args), "");
    (*args)++;
}

/*
** Determines whether or not a given
** argument string is a variable name or
** not. This is a wrapper function around
** sh_strisname, as the given argument may
** contain a legal '=' character.
*/
static bool is_variable_name(const char *str)
{
    char *sep = strchr(str, '=');
    bool is_valid;

    if (sep)
        *sep = '\0';
    is_valid = sh_strisname(str, "set");
    if (sep)
        *sep = '=';
    return is_valid;
}

/*
** Implementation for the shell's builtin
** set command.
** This command allows the user to set local
** variables.
*/
int builtin_set(char *args[], sh_data_t *data)
{
    if (!args[1]) {
        sh_symbols_print(data->local_vars, "\t");
        return 0;
    }
    args++;
    while (*args) {
        if (!is_variable_name(*args))
            return 1;
        parse_set_arg(&args, data);
    }
    return 0;
}
