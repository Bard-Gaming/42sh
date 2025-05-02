/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** builtin_unset
*/

#include <42sh/builtins.h>
#include <42sh/symbols.h>
#include <42sh/data.h>
#include <42sh/io.h>


/*
** Implementation for the shell's builtin
** unset command.
** This command allows the user to unset /
** undefine local variables.
*/
int builtin_unset(char *args[], sh_data_t *data)
{
    if (args[1] == NULL) {
        sh_puterr("unset: Too few arguments.\n");
        return 1;
    }
    args++;
    while (*args != NULL) {
        sh_symbols_unset(data->local_vars, *args);
        args++;
    }
    return 0;
}
