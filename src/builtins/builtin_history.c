/*
** EPITECH PROJECT, 2025
** history
** File description:
** history
*/

#include <stdio.h>
#include <stdlib.h>
#include <42sh/shell.h>

int builtin_history(void)
{
    size_t count;
    size_t i;
    char *cmd;

    count = shell_history_count();
    for (i = 1; i <= count; i++) {
        cmd = shell_history_get(i);
        if (cmd != NULL) {
            printf("%zu  %s\n", i, cmd);
            free(cmd);
        }
    }
    return 0;
}
