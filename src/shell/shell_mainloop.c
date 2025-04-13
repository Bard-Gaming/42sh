/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_mainloop
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <42sh/io.h>
#include <readline.h>
#include <unistd.h>


/*
** The shell's main process runtime.
** Everything the shell does is started
** here.
*/
void shell_mainloop(sh_data_t *data)
{
    char *input;

    signal_init(data);
    data->is_running = true;
    while (data->is_running) {
        input = shell_query_input(data);
        if (input == NULL)
            break;
        shell_system(input, data);
    }
    if (isatty(0) && input == NULL)
        sh_putstr("\n");
    readline_free();
}
