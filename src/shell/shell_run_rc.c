/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_run_rc
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <42sh/string.h>
#include <stdlib.h>


/*
** Runs the shell's read command script.
** If the file doesn't exist, this function
** silently does nothing (as expected).
** The shell's read command script is located
** at $HOME/.42shrc
*/
void shell_run_rc(sh_data_t *data)
{
    char *argv[] = { sh_strdup(data->shell_path), NULL };
    char *rc_abs_path = sh_strjoin(
        sh_data_getvar(data, "HOME"), SHELL_RC_PATH
    );

    shell_run_file(data, rc_abs_path, argv);
    free(rc_abs_path);
    free(argv[0]);
}
