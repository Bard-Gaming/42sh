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


static char *get_git_branch(void)
{
    FILE *stream = fopen(".git/HEAD", "r");
    char *buff = NULL;
    size_t bytes = 0;
    size_t len = 0;
    char *git_branch = NULL;
    char *res = NULL;

    if (!stream)
        return NULL;
    bytes = getline(&buff, &len, stream);
    if (bytes > 0)
        git_branch = strrchr(buff, '/');
    if (!git_branch)
        return NULL;
    git_branch[strcspn(git_branch, "\n")] = '\0';
    res = malloc(strlen(git_branch) + 3);
    sprintf(res, " (%s)", ++git_branch);
    free(buff);
    fclose(stream);
    return res;
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
        return get_git_branch();
    default:
        return strdup(code_str);
    }
}

static char *parse_prompt(char *ps1, sh_data_t *data)
{
    char *res = calloc(1024, 1);
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

char *get_prompt(char *ps1_var, sh_data_t *data)
{
    char *prompt = parse_prompt(ps1_var, data);

    return prompt;
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

    prompt = get_prompt(strdup(ps1_var), data);
    sh_putstr(prompt);
    free(prompt);
}
