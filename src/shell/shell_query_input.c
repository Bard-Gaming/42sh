/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** shell_query_input
*/

#include <mysh/shell.h>
#include <mysh/string.h>
#include <mysh/io.h>
#include <readline.h>
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

/*
** Query the user for input.
** Displays a visual prompt if
** currently in a tty.
*/
char *shell_query_input(void)
{
    if (isatty(0))
        display_prompt();
    return readline(0);
}
