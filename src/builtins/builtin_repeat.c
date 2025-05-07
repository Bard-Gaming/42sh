/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtin_repeat
*/

#include <42sh/builtins.h>
#include <42sh/string.h>
#include <42sh/shell.h>
#include <42sh/data.h>
#include <42sh/io.h>
#include <stdlib.h>


/*
** Error to return when too few
** arguments are given.
*/
static int too_few_arguments(void)
{
    sh_puterr("repeat: Too few arguments.\n");
    return 1;
}

/*
** Error to return when the number
** is invalid.
*/
static int badly_formed_number(void)
{
    sh_puterr("repeat: Badly formed number.\n");
    return 1;
}

/*
** Implementation for the shell's builtin
** repeat command.
** This command allows the user to repeat
** a given command a certain number of times.
*/
int builtin_repeat(char *args[], sh_data_t *data)
{
    unsigned long long nb;

    if (args[1] == NULL || args[2] == NULL)
        return too_few_arguments();
    if (!sh_strisnum(args[1]))
        return badly_formed_number();
    nb = strtoull(args[1], NULL, 10);
    for (unsigned long long i = 0; i < nb; i++) {
        if (data->interrupt)
            break;
        shell_exec_command(args + 2, data);
    }
    data->interrupt = false;
    return 0;
}
