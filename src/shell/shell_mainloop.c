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
** EOF Input handler.
** Tells the shell to stop running, unless
** the special <ignoreeof> variable has been
** set.
*/
static void handle_input_eof(sh_data_t *data)
{
    if (sh_symbols_get(data->local_vars, "ignoreeof"))
        puts("Use \"exit\" to leave Multishell.");
    else
        data->is_running = false;
}

/*
** The shell's main process runtime.
** Everything the shell does is started
** here.
*/
void shell_mainloop(sh_data_t *data)
{
    char *input = NULL;

    shell_init(data);
    if (isatty(0))
        shell_run_rc(data);
    data->is_running = true;
    while (data->is_running) {
        shell_update_prompt(data);
        input = shell_query_input(data);
        if (input == NULL) {
            handle_input_eof(data);
            continue;
        }
        shell_system(input, data);
    }
    if (isatty(0) && input == NULL)
        sh_putstr("\n");
}
