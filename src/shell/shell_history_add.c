/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** shell_history_add
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <42sh/string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static FILE *open_history(const sh_data_t *data)
{
    char *path = sh_strjoin(
        sh_data_getvar(data, "HOME"), SHELL_HIST_PATH
    );
    FILE *file = fopen(path, "a");

    free(path);
    return file;
}

void sh_history_add_line(const char *line)
{
    sh_data_t *data = sh_data_get();
    FILE *file = open_history(data);

    if (file != NULL) {
        fprintf(file, "%s\n", line);
        fclose(file);
    }
}
