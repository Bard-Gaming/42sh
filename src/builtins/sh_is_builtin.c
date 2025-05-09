/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_is_builtin
*/

#include <42sh/builtins.h>
#include <string.h>


/*
** Determines whether a command will
** be displayed as a builtin, i.e.
** if the given command is a builtin-like
** command.
*/
static bool is_builtin_like(const char *name)
{
    return
        strcmp(name, "foreach") == 0 ||
        strcmp(name, "while") == 0 ||
        strcmp(name, "if") == 0;
}

/*
** Tells whether or not the given command
** is a builtin or not.
*/
bool sh_is_builtin(const char *name)
{
    if (is_builtin_like(name))
        return true;
    return (bool)sh_get_builtin(name);
}
