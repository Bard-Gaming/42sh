/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtin_repeat
*/

#include <42sh/builtins.h>
#include <42sh/shell.h>
#include <42sh/data.h>
#include <42sh/env.h>
#include <42sh/io.h>
#include <readline.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static bool is_number(const char *string)
{
    while (*string != '\0') {
        if (!('0' <= *string && *string <= '9'))
            return false;
        string++;
    }
    return true;
}

int builtin_reload(char *args[], sh_data_t *data)
{
    if (!args[1] || (!args[1] && !args[2])) {
        sh_puterr("repeat: Too few arguments.\n");
        return 1;
    }
    if (!isnumber(args[1])) {
        sh_puterr("repeat: Badly formed number.\n");
        return 1;
    }
    for (int i = 0; i < (getnbr(args[1])); i++) {
        shell_exec_command((args + 2), data);
    }
}
