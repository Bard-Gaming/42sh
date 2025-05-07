/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_data_getvar
*/

#include <42sh/data.h>
#include <42sh/string.h>
#include <42sh/symbols.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


static char *get_exit_status(const sh_data_t *data)
{
    static char buffer[ITOA_MAX];

    sh_itoa(buffer, data->exit_status);
    return buffer;
}

/*
** Retrieves a variable's value from
** the shell's data. To retrieve a
** variable's value, this functions
** looks up the variables in the
** shell's symbol tables, in the
** following order:
** - Special Variables
** - Local Variables
** - User Environment Variables
** - Internal Environment Variables
** If the given variable isn't defined
** in any of the above symbol tables,
** NULL is returned instead.
*/
const char *sh_data_getvar(const sh_data_t *data, const char *name)
{
    const char *value;

    if (strcmp(name, "?") == 0)
        return get_exit_status(data);
    value = sh_symbols_get(data->local_vars, name);
    if (value != NULL)
        return value;
    value = sh_symbols_get(data->env, name);
    if (value != NULL)
        return value;
    return sh_symbols_get(data->env_internal, name);
}
