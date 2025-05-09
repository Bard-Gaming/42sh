/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_init
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <42parser/config.h>
#include <readline.h>

/*
** Initializes the shell.
** This calls all specific initialization
** functions, and acts as a helper function
** to initialize everything the shell needs.
*/
void shell_init(sh_data_t *data)
{
    sh_data_register(data);
    signal_init();
    readline_configure(
        shell_autocomplete,
        shell_autocomplete_long,
        shell_history_get
    );
    parser_config_set_substitute(shell_alias);
}
