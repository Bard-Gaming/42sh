/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Header file for all
** shell types
*/

#ifndef SHELL_TYPES_H
    #define SHELL_TYPES_H
    #include <42parser/ast.h>


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
//               Enumerations              //
//                                         //
/////////////////////////////////////////////

typedef enum sh_command_state sh_command_state_t;  // Defined in data.h


/////////////////////////////////////////////
//                                         //
//                 Functions               //
//                                         //
/////////////////////////////////////////////

typedef int (*exec_fnc_t)(char **args, sh_data_t *data);
typedef int (*builtin_cmd_t)(char *args[], sh_data_t *data);
typedef void (*sh_interpret_fnc_t)(ast_t *ast, sh_data_t *data);


#endif
