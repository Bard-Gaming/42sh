/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** shell_query_command
*/

#include <mysh/shell.h>
#include <mysh/io.h>
#include <unistd.h>
#include <stdio.h>


ssize_t shell_query_command(char **restrict lineptr,
    size_t *restrict n, FILE *restrict stream)
{
    if (isatty(0))
        sh_putstr("$> ");
    return getline(lineptr, n, stream);
}
