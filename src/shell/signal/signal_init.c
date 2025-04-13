/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** signal_init
*/

#include <42sh/shell.h>
#include <signal.h>


/*
** Initializes the shell's
** signal hooks.
*/
void signal_init(sh_data_t *data)
{
    signal_interrupt_init(data);
    signal(SIGINT, signal_interrupt);
}
