/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_vector_glob
*/

#include <42sh/vector.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>


/*
** Globs all arguments present in the given
** argument vector. This function is assumed
** to never fail, as if globbing fails,
** pglob->gl_pathc will be left unchanged,
** which is perfectly valid.
*/
static void glob_arguments(sh_vector_t *argv, glob_t *pglob)
{
    int flags = GLOB_NOCHECK | GLOB_TILDE | GLOB_BRACE;

    glob(argv->data[0], flags, NULL, pglob);
    flags |= GLOB_APPEND;
    for (size_t i = 1; i < argv->count; i++)
        glob(argv->data[i], flags, NULL, pglob);
}

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
** Applies globbing to all elements of the
** given vector. This assumes the given vector
** is a vector of strings, and may not be called
** with a vector containing any amount of
** non-strings.
** This does nothing if the given argument vector
** is empty.
*/
void sh_vector_glob(sh_vector_t *argv, bool sanitize)
{
    glob_t pglob = { 0 };

    if (argv->count == 0)
        return;
    glob_arguments(argv, &pglob);
    if (sanitize)
        sanitize_glob(&pglob);
    sh_vector_delete(argv, NULL);
    argv->count = pglob.gl_pathc;
    argv->capacity = pglob.gl_offs;
    argv->data = (void *)pglob.gl_pathv;
}
