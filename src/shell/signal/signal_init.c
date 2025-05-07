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
void signal_init(void)
{
    signal(SIGINT, signal_interrupt);
}
