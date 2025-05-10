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
#include <readline/terminal.h>
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
** Runs the shell's mainloop in TTY mode.
** This is different from the default mode,
** as this doesn't exit if EOT is received
** and "ignoreeof" is set, as well as having
** some more display options.
*/
static void tty_mainloop(sh_data_t *data)
{
    char *input = NULL;

    shell_run_rc(data);
    sh_putstr(CURSOR_LINE);
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
    sh_putstr(CURSOR_BLOCK);
    sh_putstr("\n");
}

/*
** Runs the shell's default mainloop.
** This is boring mode, meaning the
** shell's prompt won't be updated,
** ignoreeof won't be handled, and
** all custom styles won't be applied.
**
*/
static void default_mainloop(sh_data_t *data)
{
    char *input = NULL;

    data->is_running = true;
    while (data->is_running) {
        input = shell_query_input(data);
        if (input == NULL)
            break;
        shell_system(input, data);
    }
}

/*
** The shell's main process runtime.
** Everything the shell does is started
** here.
*/
void shell_mainloop(sh_data_t *data)
{
    if (isatty(0))
        return tty_mainloop(data);
    return default_mainloop(data);
}
