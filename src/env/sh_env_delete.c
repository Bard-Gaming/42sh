/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_data_del_unix_env
*/

#include <42sh/data.h>
#include <stdlib.h>


/*
** Deletes a unix envioronment,
** freeing all of the memory allocated
** to store its data.
*/
void sh_env_delete(char **env)
{
    char **current = env;

    if (env == NULL)
        return;
    while (*current != NULL) {
        free(*current);
        current++;
    }
    free(env);
}
