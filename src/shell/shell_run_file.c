/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_run_file
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <42sh/string.h>
#include <readline.h>
#include <unistd.h>
#include <fcntl.h>


/*
** Runs the script within the file pointed
** to by the given path.
** This returns the exit status of the script,
** or a negative number if an error occured.
*/
#include <stdio.h>
int shell_run_file(sh_data_t *data, const char *path, char *args[])
{
    int file = open(path, O_RDONLY);
    char arg_name[ITOA_MAX];
    char *file_source;

    if (file < 0)
        return -1;
    for (int i = 0; args[i] != NULL; i++) {
        sh_itoa(arg_name, i);
        sh_data_setvar(data, arg_name, args[i]);
    }
    file_source = readline(file, NULL);
    while (file_source != NULL) {
        shell_system(file_source, data);
        file_source = readline(file, NULL);
    }
    close(file);
    return data->exit_status;
}
