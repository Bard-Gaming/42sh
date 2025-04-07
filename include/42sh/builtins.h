/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Header file for all
** minishell builtins
*/

#ifndef SHELL_BUILTINS_H
    #define SHELL_BUILTINS_H
    #include <42sh/types.h>


builtin_cmd_t builtin_get(const char *name);

// Builtins:
int builtin_cd(char *args[], sh_data_t *data);
int builtin_env(char *args[], sh_data_t *data);
int builtin_exec(char *args[], sh_data_t *data);
int builtin_exit(char *args[], sh_data_t *data);
int builtin_reload(char *args[], sh_data_t *data);
int builtin_setenv(char *args[], sh_data_t *data);
int builtin_unsetenv(char *args[], sh_data_t *data);


#endif
