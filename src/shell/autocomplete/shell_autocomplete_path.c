/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_autocomplete_path
*/

#include <42sh/shell.h>
#include <42sh/symbols.h>
#include <42sh/vector.h>
#include <42sh/string.h>
#include <42sh/data.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/*
** Retrieves all paths within the PATH
** shell variable in the form of a vector.
*/
static sh_vector_t retrieve_path_directories(const sh_data_t *data)
{
    sh_vector_t result = { 0 };
    char *path = sh_strdup(sh_data_getvar(data, "PATH") ?: "");
    char *token = strtok(path, ":");

    while (token != NULL) {
        sh_vector_push_back(&result, sh_strdup(token));
        token = strtok(NULL, ":");
    }
    free(path);
    return result;
}

/*
** Determines whether the given file name
** is a valid match for the input or not.
*/
static bool is_valid_match(const char *input, const char *filename)
{
    if (filename[0] == '.')
        return false;
    return strncmp(filename, input, strlen(input)) == 0;
}

/*
** Returns a duplicate of the given file name
** if it points to an executable, and NULL if
** not.
*/
static char *build_executable(const char *dir_path, const char *filename)
{
    bool is_executable;
    char *full_path;

    asprintf(&full_path, "%s/%s", dir_path, filename);
    is_executable = access(full_path, X_OK) == 0;
    free(full_path);
    return is_executable ? strdup(filename) : NULL;
}

/*
** Adds all matches in the directory
** to the matches vector.
*/
static void add_matches(sh_vector_t *matches,
    const char *dir_path, const char *input)
{
    DIR *directory = opendir(dir_path);
    struct dirent *entry;
    char *candidate;

    if (directory == NULL)
        return;
    entry = readdir(directory);
    while (entry != NULL) {
        if (!is_valid_match(input, entry->d_name)) {
            entry = readdir(directory);
            continue;
        }
        candidate = build_executable(dir_path, entry->d_name);
        if (candidate != NULL)
            sh_vector_push_back(matches, candidate);
        entry = readdir(directory);
    }
    closedir(directory);
}

/*
** Retrieves the index of the shortest
** element in the given string vector.
*/
static size_t get_shortest_element(const sh_vector_t *vector)
{
    size_t min_index = 0;
    size_t min_length = strlen(vector->data[0]);
    size_t current_len;

    for (size_t i = 1; i < vector->count; i++) {
        current_len = strlen(vector->data[i]);
        if (current_len >= min_length)
            continue;
        min_index = i;
        min_length = current_len;
    }
    return min_index;
}

/*
** Moves the shortest element to
** the first position within the
** given vector.
*/
static void move_shortest_first(sh_vector_t *vector)
{
    size_t min_index = get_shortest_element(vector);
    void *temp;

    temp = vector->data[min_index];
    vector->data[min_index] = vector->data[0];
    vector->data[0] = temp;
}

/*
** Finds all binaries that start with the
** given input in all directories specified
** by the PATH shell variable.
*/
sh_vector_t shell_autocomplete_path(const char *input, const sh_data_t *data)
{
    sh_vector_t path_directories = retrieve_path_directories(data);
    sh_vector_t matches = { 0 };
    const char *current_dir;

    for (size_t i = 0; i < path_directories.count; i++) {
        current_dir = path_directories.data[i];
        add_matches(&matches, current_dir, input);
    }
    sh_vector_delete(&path_directories, NULL);
    if (matches.count > 0)
        move_shortest_first(&matches);
    return matches;
}
