/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** builtin_exit
*/

#include <mysh/builtins.h>
#include <mysh/string.h>
#include <mysh/io.h>
#include <stdbool.h>


static bool is_number(const char *string)
{
    while (*string != '\0') {
        if (!('0' <= *string && *string <= '9'))
            return false;
        string++;
    }
    return true;
}

static unsigned char arg_to_exit_status(const char *arg)
{
    size_t arg_length = sh_strlen(arg);
    unsigned short exit_status = 0;

    for (unsigned int i = arg_length > 3 ? 3 : arg_length; i > 0; i--) {
        exit_status *= 10;
        exit_status += arg[arg_length - i] - '0';
    }
    return exit_status % 256;
}

int builtin_exit(const char *args[], char *env[])
{
    if (args[1] == NULL)
        exit(0);
    if (args[2] != NULL || !is_number(args[1])) {
        sh_puterr("exit: Expression syntax.\n");
        return 84;
    }
    exit(arg_to_exit_status(args[1]));
}
