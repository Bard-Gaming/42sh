/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** signal_interrupt
*/

#include <42sh/shell.h>
#include <42sh/io.h>


/*
** SIGINT signal handler.
** TODO: display prompt after newline.
*/
void signal_interrupt(int code)
{
    sh_putstr("\n");
    return;
}
