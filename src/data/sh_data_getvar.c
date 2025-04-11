/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_data_getvar
*/

#include <42sh/data.h>
#include <42sh/symbols.h>
#include <stdbool.h>
#include <stdlib.h>


/*
** Determines whether or not the given
** string representation is an unsigned
** number or not.
*/
static bool is_number(const char *repr)
{
    while (*repr != '\0') {
        if (!('0' <= *repr && *repr <= '9'))
            return false;
        repr++;
    }
    return true;
}

/*
** Returns the value of a given argument.
** If the given name is not an argument index,
** NULL is returned.
** If the given name is an index, but the argument
** at that index isn't set, then an empty string
** is returned instead.
*/
static const char *get_argument(const sh_data_t *data, const char *name)
{
    unsigned long long index;

    if (!is_number(name))
        return NULL;
    index = strtoull(name, NULL, 10);
    if (index >= data->argv.count)
        return "";
    return data->argv.data[index];
}

/*
** Retrieves a variable's value from
** the shell's data. To retrieve a
** variable's value, this functions
** looks up the variables in the
** shell's symbol tables, in the
** following order:
** - Arguments (if name is 0, 1, 2, etc...)
** - Local Variables
** - User Environment Variables
** - Internal Environment Variables
** If the given variable isn't defined
** in any of the above symbol tables,
** NULL is returned instead.
*/
const char *sh_data_getvar(const sh_data_t *data, const char *name)
{
    const char *value = get_argument(data, name);

    if (value != NULL)
        return value;
    value = sh_symbols_get(data->local_vars, name);
    if (value != NULL)
        return value;
    value = sh_symbols_get(data->env, name);
    if (value != NULL)
        return value;
    return sh_symbols_get(data->env_internal, name);
}
