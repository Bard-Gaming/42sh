/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_getcwd
*/

#include <42sh/shell.h>
#include <42sh/string.h>
#include <42sh/data.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>


/*
** Retrieves the current work directory's path
** in string format. The returned string needs
** to be freed by the user.
** If an error occurs during the retrieval, NULL
** is returned instead.
** If basename is true, the returned string will
** only contain the base name of the path.
** If it is false, the absolute path is returned
** instead.
** If the absolute path matches the user's home
** directory, a string containing only a tilda
** ('~') is returned instead.
**
** Examples:
** # in /home/user/projects/user
** shell_getcwd(data, true)  -> "user"
** shell_getcwd(data, false) -> "~/projects/user"
** # in /home/user
** shell_getcwd(data, true)  -> "~"
** shell_getcwd(data, false) -> "~"
*/
char *shell_getcwd(sh_data_t *data, bool basename)
{
    const char *home_dir = sh_data_getvar(data, "HOME");
    size_t home_dir_len = strlen(home_dir);
    char path[PATH_MAX];
    char *absolute_path = path;

    if (getcwd(path, PATH_MAX) == NULL)
        return NULL;
    if (strcmp(home_dir, path) == 0)
        return strdup("~");
    if (basename)
        return sh_basename(path);
    if (home_dir_len > 0 && strncmp(path, home_dir, home_dir_len) == 0) {
        path[home_dir_len - 1] = '~';
        absolute_path += home_dir_len - 1;
    }
    return strdup(absolute_path);
}
