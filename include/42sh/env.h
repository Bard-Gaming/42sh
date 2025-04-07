/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Header file for everything
** related to the environment
*/

#ifndef SHELL_ENV_H
    #define SHELL_ENV_H
    #include <42sh/types.h>


char **sh_env_create(const sh_data_t *data);
void sh_env_delete(char **env);


#endif
