/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** builtin_set
*/

#include <42sh/builtins.h>
#include <42sh/symbols.h>
#include <42sh/data.h>



/*
** Implementation for the shell's builtin
** set command.
** This command allows the user to set local
** variables.
**
** Technical Addendum:
** The boolean negation is added, as UNIX considers
** 0 as being the value for true, whereas C and most
** other programming languages see a value of 0 as being
** false. As such, the negation only exists to convert
** C's boolean into UNIX's boolean.
*/
int builtin_set(char *args[], sh_data_t *data)
{
    return !sh_symbols_parse(data->local_vars, (const char **)args + 1);
}
