/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** builtin_get
*/

#include <42sh/builtins.h>
#include <stdlib.h>
#include <string.h>


/*
** Sub-subtrie for all commands that start with
** the letters 'ex'.
** This function shouldn't be called unless
** the name of the command actually starts
** with 'ex'.
*/
static builtin_cmd_t builtin_get_ex(const char *name)
{
    switch (*name) {
    case 'e':
        return strcmp(name + 1, "c") == 0 ? builtin_exec : NULL;
    case 'i':
        return strcmp(name + 1, "t") == 0 ? builtin_exit : NULL;
    default:
        return NULL;
    }
}

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
        return strcmp(name + 1, "v") == 0 ? builtin_env : NULL;
    case 'x':
        return builtin_get_ex(name + 1);
    default:
        return NULL;
    }
}

/*
** Subtrie for all commands that start with
** the letters "re".
** This function shouldn't be called unless
** the name of the command actually starts
** with "re".
*/
static builtin_cmd_t builtin_get_re(const char *name)
{
    switch (*name) {
    case 'l':
        return strcmp(name + 1, "oad") == 0 ? builtin_reload : NULL;
    case 'p':
        return strcmp(name + 1, "eat") == 0 ? builtin_repeat : NULL;
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
        return strcmp(name + 1, "d") == 0 ? builtin_cd : NULL;
    case 'e':
        return builtin_get_e(name + 1);
    case 'r':
        return *(name + 1) == 'e' ? builtin_get_re(name + 2) : NULL;
    case 's':
        return strcmp(name + 1, "etenv") == 0 ? builtin_setenv : NULL;
    case 'u':
        return strcmp(name + 1, "nsetenv") == 0 ? builtin_unsetenv : NULL;
    default:
        return NULL;
    }
}
