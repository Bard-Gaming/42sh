/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** builtin_get
*/

#include <mysh/builtins.h>
#include <stdlib.h>


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
        return name[1] == 'd' ? builtin_cd : NULL;
    default:
        return NULL;
    }
}
