/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** builtin_get
*/

#include <mysh/builtins.h>
#include <mysh/string.h>
#include <stdlib.h>


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
** Return a pointer to the function that
** implements the builtin command with the
** same name as <name>.
** If the given name doesn't correspond to
** a function, returns NULL instead.
*/
builtin_cmd_t builtin_get(const char *name)
{
    switch (name[0]) {
    case 'c':
        return sh_strcmp(name + 1, "d") == 0 ? builtin_cd : NULL;
    case 'e':
        return builtin_get_e(name + 1);
    case 's':
        return sh_strcmp(name + 1, "etenv") == 0 ? builtin_setenv : NULL;
    default:
        return NULL;
    }
}
