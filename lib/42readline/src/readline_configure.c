/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** readline_configure
*/

#include <readline.h>
#include <readline/buffer.h>
#include <string.h>
#include <stdio.h>


/*
** Default autocomplete function.
** Duplicating the input is a requirement,
** as readline will inevitably call free()
** on the result once it doesn't need it
** anymore.
*/
static char *default_autocomplete(const char *input)
{
    return strdup("valgrind");
}

/*
** Default long autocomplete function.
** This should print all possible autocompletions
** for the given input.
*/
static void default_autocomplete_long(const char *input)
{
    puts("valgrind");
}

void readline_configure(autocomplete_fnc_t autocomplete,
    long_autocomplete_fnc_t autocomplete_long)
{
    string_buffer_t *buffer = rl_buffer_get();

    buffer->autocomplete =
        autocomplete ?: default_autocomplete;
    buffer->autocomplete_long =
        autocomplete_long ?: default_autocomplete_long;
}
