/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** builtin_unsetenv
*/

#include <mysh/builtins.h>
#include <mysh/data.h>
#include <mysh/env.h>
#include <mysh/io.h>
#include <stddef.h>


/*
** Implementation for the shell's builtin
** unsetenv command.
** This command unsets/removes all environment
** variables specified as arguments.
** If the given variable name is invalid or already
** unset, this command does nothing and moves on to
** the next variable name (if any).
*/
int builtin_unsetenv(char *args[], sh_data_t *data)
{
    if (args[1] == NULL) {
        sh_puterr("unsetenv: Too few arguments.\n");
        return 84;
    }
    args++;
    while (*args != NULL) {
        sh_env_unset(data->env, *args);
        args++;
    }
    return 0;
}
