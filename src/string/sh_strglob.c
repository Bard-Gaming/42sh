/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_strglob
*/

#include <42sh/string.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>


/*
** Returns true if the given path is
** "." or "..", and false otherwise.
*/
static bool is_undesired(const char *path)
{
    if (path[0] != '.')
        return false;
    if (path[1] == '\0')
        return true;
    return
        path[1] == '.' &&
        path[2] == '\0';
}

/*
** Removes the element at index i.
** This preserves order, meaning it
** is relatively slow.
*/
static void remove_element(glob_t *pglob, size_t index)
{
    free(pglob->gl_pathv[index]);
    for (size_t i = index; i < pglob->gl_pathc; i++)
        pglob->gl_pathv[i] = pglob->gl_pathv[i + 1];
    pglob->gl_pathc--;
}

/*
** Removes unwanted elements from the result
** of globbing. Undesired results are the
** special dirs '.' and '..'.
*/
static void sanitize_glob(glob_t *pglob)
{
    for (size_t i = 0; i < pglob->gl_pathc; i++) {
        if (!is_undesired(pglob->gl_pathv[i]))
            continue;
        remove_element(pglob, i);
        i--;
    }
}

/*
** Apply globbing to the given string.
** If there is nothing to be done, a copy
** of the string is returned instead.
*/
char *sh_strglob(const char *str, bool skip_undesired)
{
    glob_t pglob = { 0 };
    char *result;
    int flags = GLOB_NOCHECK | GLOB_TILDE | GLOB_BRACE;

    if (strcmp(str, ".") == 0 || strcmp(str, "..") == 0)
        return sh_strdup(str);
    glob(str, flags, NULL, &pglob);
    if (skip_undesired)
        sanitize_glob(&pglob);
    result = sh_strjoinvec((const char **)pglob.gl_pathv, " ");
    globfree(&pglob);
    return result;
}
