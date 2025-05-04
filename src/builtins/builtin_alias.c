/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** builtin_alias
*/

#include <42sh/builtins.h>
#include <42sh/symbols.h>
#include <42sh/string.h>
#include <42sh/data.h>
#include <stdlib.h>
#include <stdio.h>


static int print_alias(const sh_symbols_t *table, const char *command)
{
    if (sh_symbols_get(table, command))
        puts(sh_symbols_get(table, command));
    return 0;
}

/*
** Implementation for the shell's builtin
** alias command.
** This command allows the user to set command
** aliases.
**
** Technical Addendum:
** The boolean negation is added, as UNIX considers
** 0 as being the value for true, whereas C and most
** other programming languages see a value of 0 as being
** false. As such, the negation only exists to convert
** C's boolean into UNIX's boolean.
*/
int builtin_alias(char *args[], sh_data_t *data)
{
    char *command;
    char *alias_value;

    if (args[1] == NULL) {
        sh_symbols_print(data->aliases, "\t");
        return 0;
    }
    command = args[1];
    if (args[2] == NULL)
        return print_alias(data->aliases, command);
    alias_value = sh_strjoinvec((const char **)args + 2, " ");
    sh_symbols_set(data->aliases, command, alias_value);
    free(alias_value);
    return 0;
}
