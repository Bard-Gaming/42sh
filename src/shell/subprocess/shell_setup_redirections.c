/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_setup_redirections
*/

#include <mysh/shell.h>
#include <mysh/data.h>
#include <unistd.h>


/*
** Sets up files for redirection.
**
** This function should only be called within
** a subprocess, as the original io files aren't
** restored.
**
** Note:
** The original file in data->io_files[file]
** shouldn't be closed, as it could, and most
** likely is, another actively used file
** descriptor.
*/
void shell_setup_redirections(sh_data_t *data)
{
    for (int file = 0; file < 3; file++)
        dup2(data->io_files[file], file);
}
