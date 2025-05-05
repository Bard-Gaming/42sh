/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_init
*/

#include <42sh/shell.h>
#include <42sh/data.h>
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
    shell_init_parser(data);
    readline_configure(shell_autocomplete);
}
