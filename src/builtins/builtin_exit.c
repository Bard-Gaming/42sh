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

static int exit_program(unsigned char status, sh_data_t *data)
{
    if (data->write_file == 1)
        exit(status);
    return status;
}

int builtin_exit(char *args[], sh_data_t *data)
{
    if (args[1] == NULL)
        return exit_program(data->exit_status, data);
    if (args[2] != NULL || !is_number(args[1])) {
        sh_puterr("exit: Expression syntax.\n");
        return 84;
    }
    return exit_program(arg_to_exit_status(args[1]), data);
}
