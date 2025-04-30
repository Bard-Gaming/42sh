/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_data_delete
*/

#include <42sh/data.h>
#include <42sh/symbols.h>
#include <stdlib.h>


/*
** Delete the given shell data structure
** and free all of its containing memory.
** Does nothing if the given ptr is NULL.
*/
void sh_data_delete(sh_data_t *data)
{
    if (data == NULL)
        return;
    sh_symbols_delete(data->local_vars);
    sh_symbols_delete(data->env);
    sh_symbols_delete(data->env_internal);
    free(data->shell_path);
    free(data->prompt_str);
    free(data);
}
