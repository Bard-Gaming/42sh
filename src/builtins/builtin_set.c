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
static void parse_symbol_attr(sh_symbols_t *table, const char **args[])
{
    char *sep = strchr(**args, '=');

    if (sep != NULL) {
        *sep = '\0';
        sh_symbols_set(table, **args, sep + 1);
        (*args)++;
        return;
    }
    if ((*args)[1] && strcmp((*args)[1], "=") == 0) {
        sh_symbols_set(table, (**args), (*args)[2] ?: "");
        (*args) += 3;
        return;
    }
    sh_symbols_set(table, (**args), "");
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

    if (sep != NULL)
        *sep = '\0';
    is_valid = sh_strisname(str, "set");
    if (sep != NULL)
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
    if (args[0] == NULL) {
        sh_symbols_print(data->local_vars, "\t");
        return 0;
    }
    while (*args != NULL) {
        if (!is_variable_name(*args))
            return 1;
        parse_symbol_attr(data->local_vars, (const char ***)&args);
    }
    return 0;
}
