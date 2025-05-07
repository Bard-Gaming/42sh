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

static bool is_valid_exec_match(const char *file_name, const char *prefix)
{
    return strncmp(file_name, prefix, strlen(prefix)) == 0;
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

    if (!is_valid_exec_match(entry->d_name, prefix))
        return;
    candidate = try_build_exec(dir_path, entry->d_name);
    if (candidate)
        update_best_match(best_match, candidate);
}

static char *search_loop(DIR *dir, const char *dir_path, const char *prefix)
{
    struct dirent *entry;
    char *best_match = NULL;

    entry = readdir(dir);
    while (entry) {
        handle_entry(dir_path, prefix, entry, &best_match);
        entry = readdir(dir);
    }
    return best_match;
}

char *search_executable_in_dir(const char *dir_path, const char *prefix)
{
    DIR *dir = opendir(dir_path);
    char *res = NULL;

    if (!dir)
        return NULL;
    res = search_loop(dir, dir_path, prefix);
    closedir(dir);
    return res;
}
