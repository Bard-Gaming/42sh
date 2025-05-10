/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Header file for 42readline's
** configuration
*/

#ifndef LIB_READLINE_CONFIG_H
    #define LIB_READLINE_CONFIG_H
    #include <readline.h>

    #define UNUSED __attribute__((unused))


typedef struct {
    autocomplete_fnc_t autocomplete;
    long_autocomplete_fnc_t autocomplete_long;
    history_fnc_t history;
} readline_config_t;


readline_config_t *rl_config_get(void);


#endif
