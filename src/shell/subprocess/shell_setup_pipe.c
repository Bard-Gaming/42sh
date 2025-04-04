/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_setup_pipe
*/

#include <mysh/shell.h>
#include <mysh/data.h>
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
        if (data->prev_subproc >= 0)
            waitpid(data->prev_subproc, NULL, 0);
        dup2(data->write_file, 1);
        close(data->write_file);
    }
    if (data->read_file != 0) {
        dup2(data->read_file, 0);
        close(data->read_file);
    }
}
