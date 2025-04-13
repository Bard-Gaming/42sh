/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_basename
*/

#include <42sh/string.h>
#include <string.h>


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
**
** Note:
** The output will always be a newly allocated
** string which needs to be freed by the user.
*/
char *sh_basename(const char *restrict path)
{
    char *basename = strrchr(path, '/');

    if (basename == NULL)
        return strdup(path);
    return strdup(basename + 1);
}
