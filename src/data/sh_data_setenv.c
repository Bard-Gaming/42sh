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
** Set's the environment variable, as
** specified by name, to the given value.
*/
void sh_data_setenv(sh_data_t *data, const char *name, const char *value)
{
    sh_symbols_set(data->env, name, value);
}
