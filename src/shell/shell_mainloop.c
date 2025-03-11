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
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


void shell_mainloop(sh_data_t *data)
{
    char *raw_input = shell_query_input();
    ast_t *parsed_input = NULL;

    while (raw_input != NULL) {
        ast_delete(parsed_input);
        parsed_input = parse_line(raw_input);
        shell_interpret_input(parsed_input, data);
        free(raw_input);
        raw_input = shell_query_input();
    }
    if (isatty(0))
        sh_putstr("\n");
}
