/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_data_setvar
*/

#include <42sh/data.h>
#include <42sh/symbols.h>


/*
** Set's the local variable, as specified
** by name, to the given value.
*/
void sh_data_setvar(sh_data_t *data, const char *name, const char *value)
{
    sh_symbols_set(data->local_vars, name, value);
}
