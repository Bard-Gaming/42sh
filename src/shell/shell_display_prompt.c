/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_display_prompt
*/

#include <42sh/shell.h>
#include <42sh/string.h>
#include <42sh/data.h>
#include <42sh/io.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
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
        branch_name = strdup(branch_name + 1);
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
        return strdup("");
    branch_name = fetch_git_branch(stream);
    fclose(stream);
    if (branch_name == NULL)
        return strdup("");
    asprintf(
        &result,
        COLOR_RESET " (" COLOR_GREEN "%s" COLOR_RESET ")",
        branch_name
    );
    free(branch_name);
    return result ?: strdup("");
}

/*
** Gets the value of a given prompt
** format. This always returns an
** allocated character buffer that
** needs to be freed by the user.
*/
static char *get_format_value(char code, sh_data_t *data)
{
    char code_str[2] = { code, '\0' };

    switch (code) {
    case 'u':
            return strdup(sh_data_getvar(data, "USER"));
    case 'w':
        return getcwd(NULL, 0);
    case 'W':
        return sh_basename(NULL);
    case 'g':
        return get_formatted_branch();
    default:
        return strdup(code_str);
    }
}

static char *parse_prompt(char *ps1, sh_data_t *data)
{
    char *res = calloc(1024, sizeof(char));
    char *insert;
    char *tmp;

    for (int i = 0; ps1[i]; i++) {
        if (ps1[i] == '\\' && ps1[i + 1]) {
            i++;
            insert = get_format_value(ps1[i], data);
        } else {
            insert = calloc(2, 1);
            insert[0] = ps1[i];
        }
        tmp = sh_strjoin(res, insert);
        free(res);
        free(insert);
        res = tmp;
    }
    free(ps1);
    return res;
}

/*
** Displays the prompt in the standard
** output. This should only be done in
** TTY mode, so not as to cloud the
** actual output of the given command.
*/
void shell_display_prompt(sh_data_t *data)
{
    const char *ps1_var = sh_data_getvar(data, "PS1");
    char *prompt = NULL;

    prompt = parse_prompt(strdup(ps1_var), data);
    sh_putstr(prompt);
    free(prompt);
}
