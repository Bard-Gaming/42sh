/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parser_config_get
*/

#include <42parser/config.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


static char *default_substitute(const char *str)
{
    char *dup = strdup(str);

    if (dup == NULL) {
        fputs("42parser: critical memory error\n", stderr);
        exit(84);
    }
    return dup;
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
