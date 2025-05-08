/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_update_prompt
*/

#include <42sh/shell.h>
#include <42sh/symbols.h>
#include <42sh/memory.h>
#include <42sh/vector.h>
#include <42sh/string.h>
#include <42sh/data.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/*
** Fetches the branch name of the
** given git repository, as described
** by the given file stream.
** The given string is heap-allocated
** and needs to be freed by the user.
** If no branch name is found,
** NULL is returned instead.
*/
static char *fetch_git_branch(FILE *stream)
{
    char *lineptr = NULL;
    char *branch_name;
    ssize_t read_len;
    size_t cap = 0;

    read_len = getline(&lineptr, &cap, stream);
    if (read_len <= 0) {
        free(lineptr);
        return NULL;
    }
    if (lineptr[read_len - 1] == '\n')
        lineptr[read_len - 1] = '\0';
    branch_name = strrchr(lineptr, '/');
    if (branch_name != NULL)
        branch_name = sh_strdup(branch_name + 1);
    free(lineptr);
    return branch_name;
}

/*
** Retrieves a formatted version of the
** current branch, if it exists.
** If the branch doesn't exist, or an
** error occurs, an empty string is
** returned instead.
** Either way, the returned pointer
** needs to be passed to free().
*/
static char *get_formatted_branch(void)
{
    FILE *stream = fopen(".git/HEAD", "r");
    char *branch_name;
    char *result;

    if (stream == NULL)
        return sh_strdup("");
    branch_name = fetch_git_branch(stream);
    fclose(stream);
    if (branch_name == NULL)
        return sh_strdup("");
    (void)!asprintf(
        &result,
        COLOR_RESET " (" COLOR_GREEN "%s" COLOR_RESET ")",
        branch_name
    );
    free(branch_name);
    return result ?: sh_strdup("");
}

/*
** Gets the value of a given prompt
** format. This always returns an
** allocated character buffer that
** needs to be freed by the user.
*/
static char *get_format_value(char format, const sh_data_t *data)
{
    char raw_format[2] = { format, '\0' };

    switch (format) {
    case 'u':
        return sh_strdup(sh_data_getvar(data, "USER"));
    case 'w':
        return shell_getcwd(data, false);
    case 'W':
        return shell_getcwd(data, true);
    case 'g':
        return get_formatted_branch();
    default:
        return sh_strdup(raw_format);
    }
}

/*
** Returns a newly allocated prompt string
** containing the parsed result of the given
** format.
*/
char *parse_prompt(const char *format, const sh_data_t *data)
{
    char *res = sh_strdup("");
    char *format_value;
    char buf[2] = { 0 };

    for (int i = 0; format[i]; i++) {
        if (format[i] == '\\' && format[i + 1]) {
            i++;
            format_value = get_format_value(format[i], data);
            sh_strappend(&res, format_value);
            free(format_value);
        } else {
            buf[0] = format[i];
            sh_strappend(&res, buf);
        }
    }
    return res;
}

/*
** Displays the prompt in the standard
** output. This should only be done in
** TTY mode, so not as to cloud the
** actual output of the given command.
** TO-ADD: handle_precmd(data);
*/
void shell_update_prompt(sh_data_t *data)
{
    const char *prompt_format = sh_data_getvar(data, "PS1");
    const char *precommand = sh_symbols_get(data->aliases, "precmd");

    if (precommand)
        shell_system(precommand, data);
    free(data->prompt_str);
    data->prompt_str = parse_prompt(prompt_format, data);
}
