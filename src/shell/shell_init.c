/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_init
*/

#include <42sh/shell.h>


/*
** Initializes the shell.
** This calls all specific initialization
** functions, and acts as a helper function
** to initialize everything the shell needs.
*/
void shell_init(sh_data_t *data)
{
    signal_init(data);
    shell_init_parser(data);
}
