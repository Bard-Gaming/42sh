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
#include <stdlib.h>


/*
** Initializes arguments variables, i.e.
** $0 -> first arg,
** $1 -> second arg,
** ...
** $# -> arg count
** $* -> combined args (separated by space)
*/
static void init_special_variables(sh_data_t *data, char *args[])
{
    char nb_repr[ITOA_MAX];
    char *aggregate;
    int argc;

    if (*args == NULL)
        return;
    for (argc = 0; args[argc] != NULL; argc++) {
        sh_itoa(nb_repr, argc);
        sh_data_setvar(data, nb_repr, args[argc]);
    }
    sh_itoa(nb_repr, argc - 1);
    sh_data_setvar(data, "#", nb_repr);
    aggregate = sh_strjoinvec((const char **)args + 1, " ");
    sh_data_setvar(data, "*", aggregate);
    free(aggregate);
}

/*
** Runs the script within the file pointed
** to by the given path.
** This returns the exit status of the script,
** or a negative number if an error occured.
*/
int shell_run_file(sh_data_t *data, const char *path, char *args[])
{
    int file = open(path, O_RDONLY);
    char *file_source;

    if (file < 0)
        return -1;
    init_special_variables(data, args);
    file_source = readline(file, NULL);
    close(file);
    if (file_source == NULL)
        return -1;
    shell_system(file_source, data);
    return data->exit_status;
}
