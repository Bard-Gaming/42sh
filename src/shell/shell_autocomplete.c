/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_autocomplete
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <42sh/string.h>
#include <42sh/types.h>
#include <42sh/symbols.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>


static char *get_last_word(const char *input)
{
    const char *last = input + strlen(input);

    while (last > input && *(last - 1) != ' ' && *(last - 1) != '\t')
        last--;
    return strdup(last);
}

static char *find_in_aliases(sh_symbols_t *aliases, const char *prefix)
{
    const char *name;

    for (size_t i = 0; i < aliases->capacity; i++) {
        name = aliases->data[i].name;
        if (strncmp(name, prefix, strlen(prefix)) == 0)
            return strdup(name);
    }
    return NULL;
}

static int count_path_dirs(const char *path_var)
{
    int count = 0;

    for (const char *p = path_var; *p; p++) {
        if (*p == ':')
            count++;
    }
    return count + 1;
}

static char **split_path_var(const char *path_var)
{
    char *dup;
    char **res;
    char *token;
    int i;
    int count = count_path_dirs(path_var);

    if (!path_var)
        return NULL;
    dup = strdup(path_var);
    res = calloc(count + 1, sizeof(char *));
    token = strtok(dup, ":");
    i = 0;
    while (token) {
        res[i] = strdup(token);
        i++;
        token = strtok(NULL, ":");
    }
    free(dup);
    return res;
}

/*
** Find a binary in
** PATH environment variable
*/
char *find_in_path(sh_symbols_t *env, const char *prefix, int tab_count)
{
    const char *path_var;
    char **dirs;
    char *match;

    for (size_t i = 0; i < env->capacity; i++) {
        if (env->data[i].name && strcmp(env->data[i].name, "PATH") == 0)
            path_var = env->data[i].value;
    }
    if (!path_var)
        return NULL;
    dirs = split_path_var(path_var);
    if (!dirs)
        return NULL;
    for (int i = 0; dirs[i]; i++) {
        match = search_executable_in_dir(dirs[i], prefix, tab_count);
        if (match)
            return match;
    }
    return NULL;
}

char *autocomplete_from_alias(sh_symbols_t *aliases, char *prefix)
{
    char *match = find_in_aliases(aliases, prefix);

    if (match)
        free(prefix);
    return match;
}

char *autocomplete_from_path(sh_symbols_t *env, char *prefix, int tab_count)
{
    char *match = find_in_path(env, prefix, tab_count);

    if (match)
        free(prefix);
    return match;
}

/*
** 42sh's autocomplete function.
** This function will be passed onto
** the readline library.
*/
char *shell_autocomplete(const char *input, int tab_count)
{
    sh_data_t *data = sh_data_get();
    char *prefix;
    char *match;

    if (!input || !*input)
        return NULL;
    prefix = get_last_word(input);
    if (!prefix)
        return NULL;
    match = autocomplete_from_alias(data->aliases, prefix);
    if (match)
        return match;
    match = autocomplete_from_path(data->env, prefix, tab_count);
    if (match)
        return match;
    free(prefix);
    return NULL;
}
