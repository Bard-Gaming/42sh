/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Header file for all
** shell types
*/

#ifndef MYSH_TYPES_H
    #define MYSH_TYPES_H


/////////////////////////////////////////////
//                                         //
//                Structures               //
//                                         //
/////////////////////////////////////////////

typedef struct sh_data sh_data_t;                  // Defined in data.h
typedef struct sh_env sh_env_t;                    // Defined in env.h
typedef struct argument_buffer argument_buffer_t;  // Defined in arguments.h


/////////////////////////////////////////////
//                                         //
//                 Functions               //
//                                         //
/////////////////////////////////////////////

typedef int (*builtin_cmd_t)(char *args[], sh_data_t *data);


#endif
