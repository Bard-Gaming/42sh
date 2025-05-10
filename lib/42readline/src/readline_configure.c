/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** readline_configure
*/

#include <readline.h>
#include <readline/config.h>


void readline_configure(
    autocomplete_fnc_t autocomplete,
    long_autocomplete_fnc_t autocomplete_long,
    history_fnc_t history)
{
    readline_config_t *config = rl_config_get();

    config->autocomplete = autocomplete ?: config->autocomplete;
    config->autocomplete_long = autocomplete_long ?: config->autocomplete_long;
    config->history = history ?: config->history;
}
