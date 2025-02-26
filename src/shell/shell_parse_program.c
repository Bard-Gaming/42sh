/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** shell_parse_program
*/

#include <mysh/shell.h>
#include <mysh/string.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>


/*
** Note: this is not optimal
*/
static char *join_path(const char *path, const char *file)
{
    char *intermediate = sh_strjoin(path, "/");
    char *result = sh_strjoin(intermediate, file);

    free(intermediate);
    return result;
}

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
** Parses a command into an executable
** format (i.e. in such a way that it can
** be passed to execve without a hassle).
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
char *shell_parse_command(const char *command, sh_env_t *env)
{
    if (sh_str_contains_char(command, '/'))
        return sh_strdup(command);
    return get_command_path(command, env);
}
