/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Header file for all
** minishell builtins
*/

#ifndef MYSH_BUILTINS_H
    #define MYSH_BUILTINS_H
    #include <mysh/types.h>


builtin_cmd_t builtin_get(const char *name);

// Builtins:
int builtin_cd(const char *args[], sh_data_t *data);
int builtin_env(const char *args[], sh_data_t *data);
int builtin_exit(const char *args[], sh_data_t *data);
int builtin_setenv(const char *args[], sh_data_t *data);
int builtin_unsetenv(const char *args[], sh_data_t *data);


#endif
