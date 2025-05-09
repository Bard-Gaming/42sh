/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** builtin_exit
*/

#include <42sh/builtins.h>
#include <42sh/string.h>
#include <42sh/data.h>
#include <42sh/io.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


/*
** This function is necessary as ternary operators
** in for loop declarations are (apparently) a
** C-C2 violation (even though they shouldn't be).
*/
static unsigned int min(unsigned int a, unsigned int b)
{
    return a > b ? b : a;
}

/*
** Converts a string to a valid exit status.
** The exit status is saved within a single
** byte (hence the % 256).
** This is due to how linux stores exit
** statuses.
**
** Try running 'bash -c "exit 500"; echo $?'
** for comparison.
*/
static unsigned char arg_to_exit_status(const char *arg)
{
    size_t arg_length = strlen(arg);
    unsigned short exit_status = 0;

    for (unsigned int i = min(3, arg_length); i > 0; i--) {
        exit_status *= 10;
        exit_status += arg[arg_length - i] - '0';
    }
    return exit_status % 256;
}

/*
** Implementation for the shell's builtin
** exit command.
** This command exits the current process
** with the given exit status, if specified.
** If no exit status is sspecified, the exit
** status of the previous command is used
** instead.
*/
int builtin_exit(char *args[], sh_data_t *data)
{
    if (args[1] == NULL) {
        data->is_running = false;
        return data->exit_status;
    }
    if (args[2] != NULL || !sh_strisnum(args[1])) {
        sh_puterr("exit: Expression syntax.\n");
        return 84;
    }
    data->is_running = false;
    return arg_to_exit_status(args[1]);
}
