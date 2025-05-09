/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_get_builtin
*/

#include <42sh/builtins.h>
#include <stdlib.h>
#include <string.h>


/*
** Sub-subtrie for all commands that start with
** the letters 'wh'.
** This function shouldn't be called unless
** the name of the command actually starts
** with 'wh'.
*/
static builtin_cmd_t get_wh(const char *name)
{
    switch (*name) {
    case 'i':
        return strcmp(name + 1, "ch") == 0 ? builtin_which : NULL;
    case 'e':
        return strcmp(name + 1, "re") == 0 ? builtin_where : NULL;
    default:
        return NULL;
    }
}

/*
** Sub-subtrie for all commands that start with
** the letters 'ex'.
** This function shouldn't be called unless
** the name of the command actually starts
** with 'ex'.
*/
static builtin_cmd_t get_ex(const char *name)
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
static builtin_cmd_t get_e(const char *name)
{
    switch (*name) {
    case 'c':
        return strcmp(name + 1, "ho") == 0 ? builtin_echo : NULL;
    case 'n':
        return strcmp(name + 1, "v") == 0 ? builtin_env : NULL;
    case 'x':
        return get_ex(name + 1);
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
static builtin_cmd_t get_re(const char *name)
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
** Subtrie for all commands that start with
** the letters "set".
** This function shouldn't be called unless
** the name of the command actually starts
** with "set".
*/
static builtin_cmd_t get_set(const char *name)
{
    switch (*name) {
    case '\0':
        return builtin_set;
    case 'e':
        return strcmp(name + 1, "nv") == 0 ? builtin_setenv : NULL;
    default:
        return NULL;
    }
}

/*
** Subtrie for all commands that start with
** the letters "unset".
** This function shouldn't be called unless
** the name of the command actually starts
** with "unset".
*/
static builtin_cmd_t get_unset(const char *name)
{
    switch (*name) {
    case '\0':
        return builtin_unset;
    case 'e':
        return strcmp(name + 1, "nv") == 0 ? builtin_unsetenv : NULL;
    default:
        return NULL;
    }
}

/*
** Subtrie for all commands that start with
** the letters "un".
** This function shouldn't be called unless
** the name of the command actually starts
** with "un".
*/
static builtin_cmd_t get_un(const char *name)
{
    switch (*name) {
    case 'a':
        return strcmp(name + 1, "lias") == 0 ? builtin_unalias : NULL;
    case 's':
        return strncmp(name + 1, "et", 2) == 0 ? get_unset(name + 3) : NULL;
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
builtin_cmd_t sh_get_builtin(const char *name)
{
    switch (*name) {
    case 'a':
        return strcmp(name + 1, "lias") == 0 ? builtin_alias : NULL;
    case 'c':
        return strcmp(name + 1, "d") == 0 ? builtin_cd : NULL;
    case 'e':
        return get_e(name + 1);
    case 'r':
        return *(name + 1) == 'e' ? get_re(name + 2) : NULL;
    case 's':
        return strncmp(name + 1, "et", 2) == 0 ? get_set(name + 3) : NULL;
    case 'u':
        return name[1] == 'n' ? get_un(name + 2) : NULL;
    case 'v':
        return strcmp(name + 1, "ersion") == 0 ? builtin_version : NULL;
    case 'w':
        return name[1] == 'h' ? get_wh(name + 2) : NULL;
    default:
        return NULL;
    }
}
