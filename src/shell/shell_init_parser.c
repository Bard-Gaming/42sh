/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_init_parser
*/

#include <42sh/shell.h>
#include <42sh/symbols.h>
#include <42sh/data.h>
#include <42parser/config.h>


/*
** Essentially retrieves an alias (if it exists)
** and returns its value.
** This function needs to be in the given format,
** as this is required by the parser.
*/
static const char *alias_substitute(const char *command)
{
    sh_data_t *data = sh_data_get();

    return sh_symbols_get(data->aliases, command) ?: command;
}

/*
** Initializes 42sh configuration for the parser.
*/
void shell_init_parser(sh_data_t *data)
{
    parser_config_set_substitute(alias_substitute);
}
