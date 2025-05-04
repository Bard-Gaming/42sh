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
** Static getter function for the data pointer,
** which is required as it can't get passed as
** an argument by the parser.
*/
static sh_data_t **get_data_ptr(void)
{
    static sh_data_t *data = NULL;

    return &data;
}

/*
** Essentially retrieves an alias (if it exists)
** and returns its value.
** This function needs to be in the given format,
** as this is required by the parser.
*/
static const char *alias_substitute(const char *command)
{
    sh_data_t *data = *get_data_ptr();

    return sh_symbols_get(data->aliases, command) ?: command;
}

/*
** Initializes 42sh configuration for the parser.
*/
void shell_init_parser(sh_data_t *data)
{
    sh_data_t **ptr = get_data_ptr();

    *ptr = data;
    parser_config_set_substitute(alias_substitute);
}
