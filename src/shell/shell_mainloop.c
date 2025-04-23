/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_mainloop
*/

#include <42sh/shell.h>
#include <42sh/symbols.h>
#include <42sh/data.h>
#include <42sh/io.h>
#include <readline.h>
#include <unistd.h>
#include <stdio.h>


/*
** The shell's main process runtime.
** Everything the shell does is started
** here.
*/
void shell_mainloop(sh_data_t *data)
{
    char *input = NULL;

    signal_init(data);
    if (isatty(0))
        shell_run_rc(data);
    data->is_running = true;
    while (data->is_running) {
        input = shell_query_input(data);
        if (sh_symbols_get(data->local_vars, "ignoreeof") && input == NULL) {
            printf("Use \"exit\" to leave Multishell.\n");
            continue;
        }
        if (input == NULL)
            break;
        shell_system(input, data);
    }
    if (isatty(0) && input == NULL)
        sh_putstr("\n");
}
