/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_setup_pipe
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <sys/wait.h>


/*
** Sets io files up for piping.
**
** This function should only ever be called
** within a subprocess, as the resources
** assigned to file descriptors 0 and/or 1
** will not be restored back to their original
** state.
*/
void shell_setup_pipe(sh_data_t *data)
{
    if (data->write_file != 1) {
        dup2(data->write_file, 1);
        close(data->write_file);
    }
    if (data->read_file != 0) {
        dup2(data->read_file, 0);
        close(data->read_file);
    }
}
