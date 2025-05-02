/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtin_repeat
*/

#include <42sh/builtins.h>
#include <42sh/string.h>
#include <42sh/shell.h>
#include <42sh/io.h>
#include <stdlib.h>


/*
** Implementation for the shell's builtin
** repeat command.
** This command allows the user to repeat
** a given command a certain number of times.
*/
int builtin_repeat(char *args[], sh_data_t *data)
{
    unsigned long long nb;

    if (args[1] == NULL || args[2] == NULL) {
        sh_puterr("repeat: Too few arguments.\n");
        return 1;
    }
    if (!sh_strisnum(args[1])) {
        sh_puterr("repeat: Badly formed number.\n");
        return 1;
    }
    nb = strtoull(args[1], NULL, 10);
    for (unsigned long long i = 0; i < nb; i++)
        shell_exec_command(args + 2, data);
    return 0;
}
