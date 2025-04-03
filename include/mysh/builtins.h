/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Header file for all
** minishell builtins
*/

#ifndef MYSH_BUILTINS_H
    #define MYSH_BUILTINS_H
    #include <mysh/types.h>


builtin_cmd_t builtin_get(const char *name);

// Builtins:
int builtin_cd(char *args[], sh_data_t *data);
int builtin_env(char *args[], sh_data_t *data);
int builtin_exit(char *args[], sh_data_t *data);
int builtin_setenv(char *args[], sh_data_t *data);
int builtin_unsetenv(char *args[], sh_data_t *data);


#endif
