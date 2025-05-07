/*
** EPITECH PROJECT, 2025
** multishell
** File description:
** shell_search_by_index
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

static char *build_exec_path(const char *dir_path, const char *file)
{
    char full[PATH_MAX];

    snprintf(full, sizeof(full), "%s/%s", dir_path, file);
    return (access(full, X_OK) == 0) ? strdup(file) : NULL;
}

static char *try_build_exec(const char *dir_path, const char *file_name)
{
    char *match = build_exec_path(dir_path, file_name);

    return match;
}

static void update_best_match(char **best, char *candidate)
{
    if (!*best || strlen(candidate) < strlen(*best)) {
        free(*best);
        *best = candidate;
    } else {
        free(candidate);
    }
}

static void handle_entry(const char *dir_path, const char *prefix,
    struct dirent *entry, char **best_match)
{
    char *candidate;

    if (strncmp(entry->d_name, prefix, strlen(prefix)) == 0)
        return;
    candidate = try_build_exec(dir_path, entry->d_name);
    if (candidate)
        update_best_match(best_match, candidate);
}

static int fill_exec_matches(DIR *dir, const char
    *dir_path, const char *prefix, char **matches)
{
    struct dirent *entry;
    int count = 0;
    char *candidate;

    entry = readdir(dir);
    while (entry && count < MAX_MATCHES) {
        if (!is_valid_exec_match(entry->d_name, prefix)) {
            entry = readdir(dir);
            continue;
        }
        candidate = try_build_exec(dir_path, entry->d_name);
        if (candidate) {
            matches[count] = candidate;
            count++;
        }
        entry = readdir(dir);
    }
    return count;
}

static char *process_exec_matches(DIR *dir,
    const char *dir_path, const char *prefix)
{
    char *matches[MAX_MATCHES];
    int count;
    char *prefix_result = NULL;

    count = fill_exec_matches(dir, dir_path, prefix, matches);
    if (count > 0)
        prefix_result = get_common_prefix(matches, count);
        for (int i = 0; i < count; i++)
            free(matches[i]);
    return prefix_result;
}

static char *str_common_prefix(const char *s1, const char *s2)
{
    int i = 0;

    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return strndup(s1, i);
}

static char *get_common_prefix(char **matches, int count)
{
    char *prefix;
    char *tmp;

    if (count == 0)
        return NULL;
    prefix = strdup(matches[0]);
    for (int i = 1; i < count; i++) {
        tmp = str_common_prefix(prefix, matches[i]);
        free(prefix);
        prefix = tmp;
        if (!prefix || !*prefix)
            break;
    }
    return prefix;
}

int is_valid_exec_match(const char *filename, const char *prefix)
{
    if (strncmp(filename, prefix, strlen(prefix)) != 0)
        return 0;
    if (filename[0] == '.')
        return 0;
    return 1;
}

char *search_executable_in_dir(const char *dir_path,
    const char *prefix, int tab_count)
{
    DIR *dir = opendir(dir_path);
    char *res = NULL;

    if (!dir)
        return NULL;
    res = process_exec_matches(dir, dir_path, prefix);
    closedir(dir);
    return res;
}
