/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** builtin_get
*/

#include <mysh/builtins.h>
#include <mysh/string.h>
#include <stdlib.h>


/*
** Subtrie for all commands that start with
** the letter 'e'.
** This function shouldn't be called unless
** the name of the command actually starts
** with 'e'.
*/
static builtin_cmd_t builtin_get_e(const char *name)
{
    switch (*name) {
    case 'n':
        return sh_strcmp(name + 1, "v") == 0 ? builtin_env : NULL;
    case 'x':
        return sh_strcmp(name + 1, "it") == 0 ? builtin_exit : NULL;
    default:
        return NULL;
    }
}

/*
** Retrieves a builtin based on the given
** command name.
** If the given command name isn't a builtin,
** NULL is returned instead.
**
** Technical Addendum:
** This implementation of the builtin_get function
** uses a trie for optimization purposes.
** If you are unaware of what a trie/prefix tree is,
** make sure to read up on it:
** https://en.wikipedia.org/wiki/Trie
*/
builtin_cmd_t builtin_get(const char *name)
{
    switch (*name) {
    case 'c':
        return sh_strcmp(name + 1, "d") == 0 ? builtin_cd : NULL;
    case 'e':
        return builtin_get_e(name + 1);
    case 's':
        return sh_strcmp(name + 1, "etenv") == 0 ? builtin_setenv : NULL;
    case 'u':
        return sh_strcmp(name + 1, "nsetenv") == 0 ? builtin_unsetenv : NULL;
    default:
        return NULL;
    }
}
