/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Header file for the parser's
** configuration.
*/

#ifndef PARSER_CONFIG_H
    #define PARSER_CONFIG_H


typedef const char *(*substitute_fnc_t)(const char *);


typedef struct {
    substitute_fnc_t substitute;
} parser_config_t;


// User functions:
void parser_config_set_substitute(substitute_fnc_t fnc);

// Internal:
parser_config_t *parser_config_get(void);


#endif
