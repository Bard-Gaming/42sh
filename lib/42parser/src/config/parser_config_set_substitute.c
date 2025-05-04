/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parser_config_set_substitute
*/

#include <42parser/config.h>


/*
** Updates the parser config's substitute function.
*/
void parser_config_set_substitute(substitute_fnc_t fnc)
{
    parser_config_t *config = parser_config_get();

    config->substitute = fnc;
}
