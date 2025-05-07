/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_history_add
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <42sh/string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
** Opens the shell's history file
** in append text mode.
*/
static FILE *open_history(void)
{
    sh_data_t *data = sh_data_get();
    char *path = sh_strjoin(
        sh_data_getvar(data, "HOME"),
        SHELL_HIST_PATH
    );
    FILE *file = fopen(path, "at");

    free(path);
    return file;
}

/*
** Adds a command to the command history
** file (located in the user's home directory).
*/
void shell_history_add(const char *command)
{
    FILE *file = open_history();

    if (file == NULL)
        return;
    fprintf(file, "%s\n", command);
    fclose(file);
}
