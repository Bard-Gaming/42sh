/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Header file for all
** shell types
*/

#ifndef SH_TYPES_H
    #define SH_TYPES_H


/////////////////////////////////////////////
//                                         //
//                Structures               //
//                                         //
/////////////////////////////////////////////

typedef struct sh_data sh_data_t;          // Defined in data.h
typedef struct sh_env sh_env_t;            // Defined in env.h


/////////////////////////////////////////////
//                                         //
//                 Functions               //
//                                         //
/////////////////////////////////////////////

typedef int (*builtin_cmd_t)(const char *args[], sh_env_t *env);


#endif
