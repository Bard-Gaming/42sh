/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** builtin_unalias
*/

#include <42sh/builtins.h>
#include <42sh/symbols.h>
#include <42sh/data.h>
#include <42sh/io.h>


/*
** Implementation for the shell's builtin
** unalias command.
** This command allows the user to remove
** existing command aliases.
*/
int builtin_unalias(char *args[], sh_data_t *data)
{
    if (args[1] == NULL) {
        sh_puterr("unalias: Too few arguments.\n");
        return 1;
    }
    args++;
    while (*args != NULL) {
        sh_symbols_unset(data->aliases, *args);
        args++;
    }
    return 0;
}
