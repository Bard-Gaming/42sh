/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** readline_config_get
*/

#include <readline/config.h>
#include <string.h>
#include <stdio.h>


/*
** Default autocomplete function.
** Duplicating the input is a requirement,
** as readline will inevitably call free()
** on the result once it doesn't need it
** anymore.
*/
static char *default_autocomplete(UNUSED const char *input)
{
    return strdup("valgrind");
}

/*
** Default long autocomplete function.
** This should print all possible autocompletions
** for the given input.
*/
static void default_autocomplete_long(UNUSED const char *input)
{
    puts("autocomplete suggestion");
}

/*
** Default history function.
** This should set the buffer to another command
** based on the output of this function.
*/
static char *default_history(size_t index)
{
    if (index != 1)
        return NULL;
    return strdup("hihihihihi");
}

/*
** 42readline's configuration getter.
*/
readline_config_t *rl_config_get(void)
{
    static readline_config_t config = {
        .autocomplete = default_autocomplete,
        .autocomplete_long = default_autocomplete_long,
        .history = default_history,
    };

    return &config;
}
