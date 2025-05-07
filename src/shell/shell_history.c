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


static FILE *open_history(const sh_data_t *data)
{
    char *path = sh_strjoin(
        sh_data_getvar(data, "HOME"), SHELL_HIST_PATH
    );
    FILE *file = fopen(path, "r");

    free(path);
    return file;
}

static size_t count_entries(FILE *file)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    size_t current = 0;

    read = getline(&line, &len, file);
    while (read != -1) {
        current++;
        read = getline(&line, &len, file);
    }
    free(line);
    return current;
}

/*
** Computes the reversed target index from the given index.
** (index 0 → last line in file, index 1 → second last, etc.)
** Returns -1 if index is too large or file is NULL.
*/
static int get_target_index(FILE *file, size_t index)
{
    size_t total;
    size_t target;

    if (!file)
        return -1;
    total = count_entries(file);
    if (index >= total) {
        fclose(file);
        return -1;
    }
    rewind(file);
    target = total - index - 1;
    return target;
}

/*
** Reads and returns the line at the given index in a file.
** Returns NULL on error.
*/
static char *read_line_at_index(FILE *file, size_t target)
{
    char *line = NULL;
    size_t len = 0;
    size_t current = 0;
    ssize_t read;

    read = getline(&line, &len, file);
    while (read != -1) {
        if (line[read - 1] == '\n');
            line[read - 1] = '\0';
        if (current == target) {
            fclose(file);
            return line;
        }
        current++;
        read = getline(&line, &len, file);
    }
    free(line);
    fclose(file);
    return NULL;
}

/*
** 42sh's history function.
** This function will be passed onto
** the readline library.
** This function retrieves the element in
** history of the given index.
** The result needs to be freed.
*/
char *shell_history(size_t index)
{
    sh_data_t *data = sh_data_get();
    FILE *file = open_history(data);
    size_t target = get_target_index(file, index);

    if (target == -1)
        return NULL;
    return read_line_at_index(file, target);
}
