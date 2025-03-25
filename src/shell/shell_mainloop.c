/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** shell_mainloop
*/

#include <mysh/shell.h>
#include <mysh/data.h>
#include <mysh/io.h>
#include <42parser/parser.h>
#include <42parser/error.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


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
        free(raw_input);
        raw_input = shell_query_input();
    }
    ast_delete(parsed_input);
    if (isatty(0))
        sh_putstr("\n");
}
