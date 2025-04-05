/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** builtin_setenv
*/

#include <mysh/builtins.h>
#include <mysh/data.h>
#include <mysh/env.h>
#include <mysh/io.h>
#include <stdbool.h>


/*
** Returns true if the given character
** is a valid variable name character,
** and false if not.
*/
static bool is_name_char(char c)
{
    return
        ('a' <= c && c <= 'z') ||
        ('A' <= c && c <= 'Z') ||
        ('0' <= c && c <= '9') ||
        (c == '_');
}

/*
** Checks whether or not a given string
** is a valid variable name.
** Variable names are valid, if they only
** contain the following characters:
**
** - Lowercase letters
** - Uppercase letters
** - Digits (except for first char)
** - Underscore
*/
static bool is_valid_name(const char *str)
{
    if ('0' <= *str && *str <= '9') {
        sh_puterr("setenv: Variable name must begin with a letter.\n");
        return false;
    }
    while (*str != '\0') {
        if (!is_name_char(*str)) {
            sh_puterr(
                "setenv: Variable name must contain alphanumeric characters.\n"
            );
            return false;
        }
        str++;
    }
    return true;
}

/*
** Implementation for the shell's builtin
** setenv command.
** This command changes or adds environment
** variables to the shell's environment.
** If no arguments are given, the command behaves
** exactly like env would.
*/
int builtin_setenv(char *args[], sh_data_t *data)
{
    if (args[1] == NULL)
        return builtin_env(args, data);
    if (args[2] != NULL && args[3] != NULL) {
        sh_puterr("setenv: Too many arguments.\n");
        return 84;
    }
    if (!is_valid_name(args[1]))
        return 84;
    sh_env_set(data->env, args[1], args[2] == NULL ? "" : args[2]);
    return 0;
}
