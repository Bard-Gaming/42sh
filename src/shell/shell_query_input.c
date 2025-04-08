/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_query_input
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <42sh/string.h>
#include <42sh/io.h>
#include <readline.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*
** Gets the base name of the given
** path.
**
** Example:
** if the current work directory is
** "/home/user/projects", the result
** would be "projects".
*/
static char *get_basename(void)
{
    char *path = getcwd(NULL, 0);
    size_t path_len = strlen(path);
    char *basename = path;

    for (size_t i = path_len - 1; i > 0; i--) {
        if (path[i] != '/')
            continue;
        basename = strdup(path + i + 1);
        break;
    }
    if (basename != path)
        free(path);
    return basename;
}

static char *dispatch_ps1_code(char code, sh_data_t *data)
{
    char *buf;

    switch (code) {
        case 'u':
            return strdup(sh_data_getvar(data, "USER"));;
        case 'w':
            return getcwd(NULL, 0);
        case 'W':
            return get_basename();
        default: {
            buf = calloc(2, 1);
            buf[0] = code;
            return buf;
        }
    }
}

char *parse_ps1(char *ps1, sh_data_t *data)
{
    char *res = malloc(1024 * sizeof(char));
    char *insert;
    char *tmp;

    for (int i = 0; ps1[i]; i++) {
        if (ps1[i] == '\\' && ps1[i + 1]) {
            i++;
            insert = dispatch_ps1_code(ps1[i], data);
        } else {
            insert = calloc(2, 1);
            insert[0] = ps1[i];
        }
        tmp = sh_strjoin(res, insert);
        free(res);
        res = tmp;
        free(insert);
    }
    free(ps1);
    return res;
}

/*
** Displays a visual prompt for the
** user. This should only be done
** when the input is a TTY.
*/
static void display_prompt(sh_data_t *data)
{
    char *basename = get_basename();
    char *intermediate = sh_strjoin("\033[1;93m  ", basename);
    char *prompt = sh_strjoin(intermediate, "\033[0m $ ");
    char *ps1_var = (char *)sh_data_getvar(data, "PS1");

    if (ps1_var) {
        ps1_var = parse_ps1(strdup(ps1_var), data);
        sh_putstr(ps1_var);
        free(ps1_var);
    } else {
        sh_putstr(prompt);
    }
    free(basename);
    free(intermediate);
    free(prompt);
}

/*
** Query the user for input.
** Displays a visual prompt if
** the input is a TTY.
** The input is retrieved via the
** readline() function of the readline
** library (see lib/42readline).
*/
char *shell_query_input(sh_data_t *data)
{
    if (isatty(0))
        display_prompt(data);
    return readline(0);
}
