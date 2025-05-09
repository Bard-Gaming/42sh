/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_vector_glob
*/

#include <42sh/vector.h>
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
sh_vector_t glob_arg(const char *arg, bool sanitize)
{
    int flags = GLOB_NOCHECK | GLOB_TILDE | GLOB_BRACE;
    sh_vector_t result = { 0 };
    glob_t pglob = { 0 };

    if (strcmp(arg, ".") == 0 || strcmp(arg, "..") == 0) {
        sh_vector_push_back(&result, sh_strdup(arg));
        return result;
    }
    glob(arg, flags, NULL, &pglob);
    if (sanitize)
        sanitize_glob(&pglob);
    result.data = (void **)pglob.gl_pathv;
    result.count = pglob.gl_pathc;
    result.capacity = pglob.gl_offs;
    return result;
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
    sh_vector_t result = { 0 };
    sh_vector_t globbed_arg;

    for (size_t i = 0; i < argv->count; i++) {
        globbed_arg = glob_arg(argv->data[i], sanitize);
        sh_vector_move(&result, &globbed_arg);
    }
    sh_vector_delete(argv, NULL);
    *argv = result;
}
