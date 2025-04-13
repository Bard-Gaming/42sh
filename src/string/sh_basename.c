/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_basename
*/

#include <42sh/string.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>


/*
** Function responsible for treating
** sh_basename's default case. This
** is done in a separate function
** to take advantage of the stack
** (the cwd buffer doesn't need to
** be allocated this way).
*/
static char *get_default_basename(void)
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, PATH_MAX) == NULL)
        return strdup("");
    return sh_basename(cwd);
}

/*
** Returns the basename of the given path.
** If the given string is already a basename,
** i.e. if the string doesn't contain any '/'
** characters, the result will be the same as
** the path argument.
**
** Examples:
** sh_basename("/home/user/file") -> "file"
** sh_basename("file") -> "file"
** sh_basename(NULL) -> <basename of current dir>
**
** Note:
** The output will always be a newly allocated
** string which needs to be freed by the user.
*/
char *sh_basename(const char *restrict path)
{
    char *basename;

    if (path == NULL)
        return get_default_basename();
    basename = strrchr(path, '/');
    if (basename == NULL)
        return strdup(path);
    return strdup(basename + 1);
}
