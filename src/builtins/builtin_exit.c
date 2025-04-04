/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** builtin_exit
*/

#include <mysh/builtins.h>
#include <mysh/data.h>
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

/*
** This function is necessary as ternary operators
** in for loop declarations are (apparently) a
** C-C2 violation (even though they shouldn't be)
*/
static unsigned int min(unsigned int a, unsigned int b)
{
    return a > b ? b : a;
}

/*
** Converts a string to a valid exit status
** (single byte, hence the 2^8)
*/
static unsigned char arg_to_exit_status(const char *arg)
{
    size_t arg_length = sh_strlen(arg);
    unsigned short exit_status = 0;

    for (unsigned int i = min(3, arg_length); i > 0; i--) {
        exit_status *= 10;
        exit_status += arg[arg_length - i] - '0';
    }
    return exit_status % 256;
}

int builtin_exit(char *args[], sh_data_t *data)
{
    if (args[1] == NULL)
        exit(data->exit_status);
    if (args[2] != NULL || !is_number(args[1])) {
        sh_puterr("exit: Expression syntax.\n");
        return 84;
    }
    exit(arg_to_exit_status(args[1]));
}
