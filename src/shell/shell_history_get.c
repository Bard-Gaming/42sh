/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_history
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <42sh/string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
** Opens the shell's history
** file in read mode.
*/
static FILE *open_history(void)
{
    sh_data_t *data = sh_data_get();
    char *path = sh_strjoin(
        sh_data_getvar(data, "HOME"), SHELL_HIST_PATH
    );
    FILE *file = fopen(path, "r");

    free(path);
    return file;
}

/*
** Counts the amount of entries within
** the file. This is equivalent to counting
** how many newlines are present within the
** file.
*/
static size_t count_entries(FILE *file)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    size_t entry_count = 0;

    read = getline(&line, &len, file);
    while (read > 0) {
        entry_count++;
        read = getline(&line, &len, file);
    }
    free(line);
    rewind(file);
    return entry_count;
}

/*
** Reads and returns the line at the
** given index in a file.
** Returns NULL on error.
*/
static char *read_entry(FILE *file, size_t index)
{
    size_t entry_count = count_entries(file);
    size_t target = entry_count - index;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if (index >= entry_count)
        return NULL;
    for (size_t i = 0; i < target; i++) {
        read = getline(&line, &len, file);
        if (read < 0) {
            free(line);
            return NULL;
        }
    }
    if (line[read - 1] == '\n')
        line[read - 1] = '\0';
    return line;
}

/*
** 42sh's command history getter function.
** This function will be passed onto
** the readline library.
** This function retrieves the element in
** history of the given index.
** The result needs to be freed.
*/
char *shell_history_get(size_t index)
{
    FILE *file = open_history();
    char *result = read_entry(file, index);

    fclose(file);
    return result;
}
