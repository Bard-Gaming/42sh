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
#include <42parser/parser.h>
#include <42parser/error.h>
#include <readline.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


/*
** The shell's main process runtime.
** Everything the shell does is started
** here.
*/
void shell_mainloop(sh_data_t *data)
{
    char *raw_input = shell_query_input();
    ast_t *parsed_input = NULL;

    data->is_running = true;
    while (raw_input != NULL && data->is_running) {
        ast_delete(parsed_input);
        parsed_input = parse_input(raw_input);
        if (parsed_input != NULL)
            shell_interpret(parsed_input, data);
        if (P_ERRNO != 0) {
            parser_perror(NULL);
            data->exit_status = 1;
        }
        if (data->is_running)
            raw_input = shell_query_input();
    }
    readline_free();
    ast_delete(parsed_input);
    if (isatty(0) && raw_input == NULL)
        sh_putstr("\n");
}
