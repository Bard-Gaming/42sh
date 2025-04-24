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


builtin_cmd_t sh_get_builtin(const char *name);

// Shell runtime:
int builtin_reload(char *args[], sh_data_t *data);
int builtin_exec(char *args[], sh_data_t *data);
int builtin_exit(char *args[], sh_data_t *data);

// Variables:
int builtin_env(char *args[], sh_data_t *data);
int builtin_set(char *args[], sh_data_t *data);
int builtin_setenv(char *args[], sh_data_t *data);
int builtin_unset(char *args[], sh_data_t *data);
int builtin_unsetenv(char *args[], sh_data_t *data);

// Miscellaneous:
int builtin_cd(char *args[], sh_data_t *data);
int builtin_which(char *args[], sh_data_t *data);
int builtin_where(char *args[], sh_data_t *data);
int builtin_repeat(char *args[], sh_data_t *data);


#endif
