/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** signal_interrupt
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <42sh/io.h>
#include <readline.h>
#include <stdio.h>


/*
** SIGINT signal handler.
** The following function handles
** interrupt signals (usually from CTRL + C).
*/
void signal_interrupt(int code)
{
    sh_data_t *data = sh_data_get();

    (void)code;
    putchar('\n');
    if (readline_is_active())
        sh_putstr(data->prompt_str);
}
