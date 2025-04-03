/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_get_command_abs_path
*/

#include <mysh/shell.h>
#include <mysh/string.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>


/*
** Joins two paths together into a new
** buffer. The returned buffer needs to
** be freed.
**
** Example:
** join_path("test", "file.txt") -> "test/file.txt"
*/
static char *join_path(const char *path, const char *file)
{
    size_t path_len = sh_strlen(path);
    size_t file_len = sh_strlen(file);
    char *buffer = malloc(
        (path_len + file_len + 2) * sizeof(char)
    );
    char *current = buffer;

    for (size_t i = 0; i < path_len; i++) {
        *current = path[i];
        current++;
    }
    *current = '/';
    current++;
    for (size_t i = 0; i < file_len; i++) {
        *current = file[i];
        current++;
    }
    *current = '\0';
    return buffer;
}

/*
** Checks whether or not a file exists.
*/
static bool is_existing_file(const char *path)
{
    struct stat stat_buf;

    return stat(path, &stat_buf) == 0;
}

/*
** Get the absolute path of a command
** using the PATH env variable.
** If the command is not in any of the
** PATH directories, NULL is returned.
** Otherwise, a heap-allocated string
** (that needs to be freed) is returned.
*/
static char *get_command_path(const char *command, sh_env_t *env)
{
    char *env_path = sh_strdup(sh_env_get(env, "PATH"));
    const char *current_path;
    char *cmd_path;

    if (env_path == NULL)
        return NULL;
    current_path = strtok(env_path, ":");
    while (current_path != NULL) {
        cmd_path = join_path(current_path, command);
        if (is_existing_file(cmd_path)) {
            free(env_path);
            return cmd_path;
        }
        free(cmd_path);
        current_path = strtok(NULL, ":");
    }
    free(env_path);
    return NULL;
}

/*
** Retrieves the absolute path of the given
** command, if it exists. If the command doesn't
** refer to a binary from a directory specified in
** PATH, a duplicate (that needs to be freed) of
** the given command is returned instead.
**
** If the command contains '/', the result
** will be unchanged, as the function assumes
** a full path to a binary was given.
** If there is no binary with the command's name
** in any of the directories in PATH, the result is
** also unchanged.
** If the command is a file in any of the PATH directories,
** the result will be the absolute path of the command.
**
** Note that whatever the result may be, the output of
** this function should always be freed.
*/
char *shell_get_command_abs_path(const char *command, sh_env_t *env)
{
    char *command_path;

    if (sh_str_contains_char(command, '/') || sh_env_get(env, "PATH") == NULL)
        return sh_strdup(command);
    command_path = get_command_path(command, env);
    return command_path == NULL ? sh_strdup(command) : command_path;
}
