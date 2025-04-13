/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** signal_interrupt
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <readline.h>
#include <stdio.h>


/*
** This is really just a function
** to share a pointer between the
** signal handler and its init
** function.
*/
static sh_data_t **get_data_ptr(void)
{
    static sh_data_t *data = NULL;

    return &data;
}

/*
** SIGINT signal handler init function.
*/
void signal_interrupt_init(sh_data_t *data)
{
    *get_data_ptr() = data;
}

/*
** SIGINT signal handler.
** The following function handles
** interrupt signals (usually from CTRL + C).
*/
void signal_interrupt(int code)
{
    sh_data_t *data = *get_data_ptr();

    putchar('\n');
    if (readline_is_active())
        shell_display_prompt(data);
}
