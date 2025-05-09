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
    char *aggregate = sh_strjoinvec((const char **)args + 1, " ");
    int status;

    status = puts(aggregate);
    free(aggregate);
    return status < 0;
}
