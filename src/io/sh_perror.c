/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_perror
*/

#include <42sh/io.h>
#include <errno.h>
#include <string.h>


/*
** Prints the current error specified
** by the errno variable in the correct
** format.
*/
void sh_perror(const char *restrict prefix)
{
    const char *error = strerror(errno);
    size_t total_size = strlen(prefix) + strlen(error) + 5;
    char formatted_error_msg[total_size];
    char *current = formatted_error_msg;

    current = strcpy(current, prefix);
    current = strcpy(current, ": ");
    current = strcpy(current, error);
    current = strcpy(current, ".\n");
    sh_puterr(formatted_error_msg);
}
