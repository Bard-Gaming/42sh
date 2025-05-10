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
** Resolves an alias, which gracefully handles
** "alias loops", i.e. unending recursive alias
** loops.
** This is a better alternative to resolve_alias_legacy,
** but it is locked behind an option due to a (stupid)
** requirement by the task givers.
*/
static char *resolve_alias(sh_data_t *data, const char *command)
{
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

/*
** Resolves aliases, but doesn't gracefully
** handle infinite recursion.
** The user would probably prefer the
** better resolve_alias() function, but this
** function is required to be the default >:(
**
** This function returns NULL on error
** (i.e. if an infinite recursion would occur).
*/
static char *resolve_alias_legacy(sh_data_t *data, const char *command)
{
    static unsigned char recursion_count = 0;
    const char *alias_value = sh_symbols_get(data->aliases, command);
    char *expanded_alias;
    char *alias_cpy;

    if (recursion_count == 50)
        return NULL;
    if (alias_value == NULL)
        return sh_strdup(command);
    alias_cpy = strdupa(alias_value);
    recursion_count++;
    expanded_alias = preparser_expand(alias_cpy, command);
    recursion_count--;
    return expanded_alias;
}

/*
** Resolves the given command alias, returning
** the resolved command. The resulting string
** needs to be free()'d by the user of this
** function.
**
** Technical Addendum:
** This function can't take a pointer to
** the shell's data as parameter, as this
** function will be passed to the shell's
** (external) parsing library.
*/
char *shell_alias(const char *command)
{
    sh_data_t *data = sh_data_get();

    if (sh_data_getvar(data, "resolvealias"))
        return resolve_alias(data, command);
    return resolve_alias_legacy(data, command);
}
