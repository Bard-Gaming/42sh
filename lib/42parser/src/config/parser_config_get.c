/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parser_config_get
*/

#include <42parser/config.h>


static const char *default_substitute(const char *str)
{
    return str;
}

/*
** Retrieves the parser's configuration
** storage.
*/
parser_config_t *parser_config_get(void)
{
    static parser_config_t config = {
        .substitute = default_substitute,
    };

    return &config;
}
