/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_vector_glob
*/

#include <42sh/vector.h>
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
** Applies globbing to all elements of the
** given vector. This assumes the given vector
** is a vector of strings, and may not be called
** with a vector containing any amount of
** non-strings.
** This does nothing if the given argument vector
** is empty.
*/
void sh_vector_glob(sh_vector_t *argv)
{
    glob_t pglob = { 0 };

    if (argv->count == 0)
        return;
    glob_arguments(argv, &pglob);
    sh_vector_delete(argv, NULL);
    argv->count = pglob.gl_pathc;
    argv->capacity = pglob.gl_offs;
    argv->data = (void *)pglob.gl_pathv;
}
