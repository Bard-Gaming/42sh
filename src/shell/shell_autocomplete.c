/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_autocomplete
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <42sh/string.h>


/*
** 42sh's autocomplete function.
** This function will be passed onto
** the readline library.
*/
char *shell_autocomplete(const char *input)
{
    sh_data_t *data = sh_data_get();

    (void)data;
    return sh_strdup(input);
}
