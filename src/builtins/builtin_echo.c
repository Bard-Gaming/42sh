/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** builtin_echo
*/

#include <42sh/builtins.h>
#include <42sh/string.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/*
** Implementation for the shell's builtin
** echo command.
** This command allows the user to print text
** as passed by the arguments.
** Returns 0 on success and 1 on error.
*/
int builtin_echo(char *args[], UNUSED sh_data_t *data)
{
    const char *format = "%s\n";
    char *aggregate;
    int status;

    args++;
    if (*args != NULL && strcmp(*args, "-n") == 0) {
        format = "%s";
        args++;
    }
    aggregate = sh_strjoinvec((const char **)args, " ");
    status = printf(format, aggregate);
    free(aggregate);
    fflush(stdout);
    return status < 0;
}
