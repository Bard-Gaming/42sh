/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** shell_query_command
*/

#include "mysh/arguments.h"
#include <mysh/shell.h>
#include <mysh/string.h>
#include <mysh/io.h>
#include <unistd.h>
#include <stdio.h>


static char *get_basename(void)
{
    char *path = getcwd(NULL, 0);
    size_t path_len = sh_strlen(path);
    char *basename = path;

    for (size_t i = path_len - 1; i > 0; i--) {
        if (path[i] != '/')
            continue;
        basename = sh_strdup(path + i + 1);
        break;
    }
    if (basename != path)
        free(path);
    return basename;
}

static void display_prompt(void)
{
    char *basename = get_basename();
    char *intermediate = sh_strjoin("\033[1;93m  ", basename);
    char *prompt = sh_strjoin(intermediate, "\033[0m $ ");

    free(basename);
    free(intermediate);
    sh_putstr(prompt);
    free(prompt);
}

static char *readline(FILE *stream)
{
    char *res = NULL;
    size_t capacity = 0;
    ssize_t read_len;

    read_len = getline(&res, &capacity, stream);
    if (read_len <= 0) {
        free(res);
        return NULL;
    }
    return res;
}

char *shell_query_command(void)
{
    char *command;
    bool is_valid_line;
    bool is_tty = isatty(0);

    do {
        if (is_tty)
            display_prompt();
        command = readline(stdin);
        if (command == NULL)
            return NULL;
        is_valid_line = arguments_is_valid_line(command);
        if (!is_valid_line)
            sh_puterr("Unmatched quote.\n");
    } while (!is_valid_line);
    return command;
}
