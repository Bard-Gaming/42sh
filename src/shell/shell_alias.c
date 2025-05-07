/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_alias
*/

#include <42sh/shell.h>
#include <42sh/symbols.h>
#include <42sh/string.h>
#include <42sh/data.h>
#include <42parser/preparser.h>
#include <stdlib.h>
#include <string.h>


/*
** Essentially retrieves an alias (if it exists)
** and returns its value.
** This function needs to be in the given format,
** as this is required by the parser.
*/
char *shell_alias(const char *command)
{
    sh_data_t *data = sh_data_get();
    const char *alias_value = sh_symbols_get(data->aliases, command);
    char *expanded_alias;
    char *alias_cpy;

    if (alias_value == NULL)
        return sh_strdup(command);
    alias_cpy = strdupa(alias_value);
    sh_symbols_unset(data->aliases, command);
    expanded_alias = preparse(alias_cpy);
    sh_symbols_set(data->aliases, command, alias_cpy);
    return expanded_alias;
}
