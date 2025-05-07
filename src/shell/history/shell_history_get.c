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
** Reads and returns the line at the
** given index in a file.
** Returns NULL on error.
*/
static char *read_entry(FILE *file, size_t index)
{
    size_t entry_count = shell_history_count();
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
    FILE *file = shell_history_open("rt");
    char *result;

    if (file == NULL)
        return NULL;
    result = read_entry(file, index);
    fclose(file);
    return result;
}
