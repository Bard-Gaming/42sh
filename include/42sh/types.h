/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Header file for all
** shell types
*/

#ifndef SHELL_TYPES_H
    #define SHELL_TYPES_H

    #define _GNU_SOURCE

    #include <42parser/ast.h>


/////////////////////////////////////////////
//                                         //
//                Structures               //
//                                         //
/////////////////////////////////////////////

typedef struct sh_data sh_data_t;                  // Defined in data.h
typedef struct sh_symbols sh_symbols_t;            // Defined in symbols.h
typedef struct sh_vector sh_vector_t;              // Defined in vector.h


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

typedef int (*exec_fnc_t)(char **, sh_data_t *);
typedef int (*builtin_cmd_t)(char *[], sh_data_t *);
typedef void (*sh_interpret_fnc_t)(ast_t *, sh_data_t *);
typedef char *(*sh_interpret_val_fnc_t)(ast_t *, sh_data_t *);
typedef void (*free_fnc_t)(void *);


#endif
