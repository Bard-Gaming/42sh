/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Header file for all
** minishell builtins
*/

#ifndef MYSH_BUILTINS_H
    #define MYSH_BUILTINS_H


typedef int (*builtin_cmd_t)(const char *args[], char *env[]);


builtin_cmd_t builtin_get(const char *name);

// Builtins:
int builtin_cd(const char *args[], char *env[]);
int builtin_exit(const char *args[], char *env[]);


#endif
