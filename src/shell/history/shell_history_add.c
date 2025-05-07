/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_history_add
*/

#include <42sh/shell.h>
#include <stdio.h>


/*
** Adds a command to the command history
** file (located in the user's home directory).
*/
void shell_history_add(const char *command)
{
    FILE *file = shell_history_open("at");

    if (file == NULL)
        return;
    fprintf(file, "%s\n", command);
    fclose(file);
}
