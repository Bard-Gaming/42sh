/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_mainloop
*/

#include <mysh/shell.h>
#include <mysh/data.h>
#include <mysh/io.h>
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

    while (raw_input != NULL) {
        ast_delete(parsed_input);
        parsed_input = parse_input(raw_input);
        if (parsed_input != NULL)
            shell_interpret(parsed_input, data);
        if (P_ERRNO != 0) {
            parser_perror(NULL);
            data->exit_status = 1;
        }
        raw_input = shell_query_input();
    }
    readline_free();
    ast_delete(parsed_input);
    if (isatty(0))
        sh_putstr("\n");
}
