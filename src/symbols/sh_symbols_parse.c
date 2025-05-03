/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_symbols_parse
*/

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

    if (sep)
        *sep = '\0';
    is_valid = sh_strisname(str, "set");
    if (sep)
        *sep = '=';
    return is_valid;
}

/*
** Parses arguments into symbol definitions.
** The given table will be modified to fit
** the symbol definitions.
** Returns true if this was successful for
** all symbols, and false if not.
*/
bool sh_symbols_parse(sh_symbols_t *table, const char *args[])
{
    if (args[0] == NULL) {
        sh_symbols_print(table, "\t");
        return true;
    }
    while (*args != NULL) {
        if (!is_variable_name(*args))
            return 1;
        parse_symbol_attr(table, &args);
    }
    return 0;
}
