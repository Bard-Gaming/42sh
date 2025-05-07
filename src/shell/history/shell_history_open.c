/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_history_open
*/

#include <42sh/shell.h>
#include <42sh/string.h>
#include <42sh/data.h>
#include <stdlib.h>
#include <stdio.h>


/*
** Opens the shell's history file
** in append text mode.
*/
FILE *shell_history_open(const char *modes)
{
    sh_data_t *data = sh_data_get();
    char *path = sh_strjoin(
        sh_data_getvar(data, "HOME"),
        SHELL_HIST_PATH
    );
    FILE *file = fopen(path, modes);

    free(path);
    return file;
}
