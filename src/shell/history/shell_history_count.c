/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_history_count
*/

#include <42sh/shell.h>
#include <stdlib.h>


/*
** Counts the amount of entries within
** the file. This is equivalent to counting
** how many newlines are present within the
** file.
*/
size_t shell_history_count(void)
{
    FILE *file = shell_history_open("rt");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    size_t entry_count = 0;

    if (file == NULL)
        return 0;
    read = getline(&line, &len, file);
    while (read > 0) {
        entry_count++;
        read = getline(&line, &len, file);
    }
    free(line);
    fclose(file);
    return entry_count;
}
