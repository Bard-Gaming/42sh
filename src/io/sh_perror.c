/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_perror
*/

#include <mysh/io.h>
#include <mysh/string.h>
#include <errno.h>
#include <string.h>


/*
** Prints the current error specified
** by the errno variable in the correct
** format.
*/
void sh_perror(const char *prefix)
{
    const char *error = strerror(errno);
    size_t total_size = sh_strlen(prefix) + sh_strlen(error) + 5;
    char formatted_error_msg[total_size];
    char *current = formatted_error_msg;

    current = sh_strcpy(current, prefix);
    current = sh_strcpy(current, ": ");
    current = sh_strcpy(current, error);
    current = sh_strcpy(current, ".\n");
    sh_puterr(formatted_error_msg);
}
