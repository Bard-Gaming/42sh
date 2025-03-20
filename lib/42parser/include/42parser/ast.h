/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Header file for all
** operations tied to
** the abstract syntax
** tree or its nodes
*/

#ifndef PARSER_ABSTRACT_SYNTAX_NODE_H
    #define PARSER_ABSTRACT_SYNTAX_NODE_H
    #include <42parser/token.h>
    #include <stdbool.h>
    #include <stddef.h>


typedef enum {
    AT_ERROR,          // <generic error>

    // Atoms:
    AT_COMMAND,        // <argument>+

    // Operations:
    AT_UNARY_JOB,      // <command>  &
    AT_COMMAND_CHAIN,  // <command>  ; <command>
    AT_OPERATION_JOB,  // <command>  & <command>
    AT_OPERATION_AND,  // <command> && <command>
    AT_OPERATION_PIPE, // <command>  | <command>
    AT_OPERATION_OR,   // <command> || <command>

    AT_COUNT,          // keep last
} ast_type_t;


typedef struct {
    char **args;
    size_t arg_count;
    size_t arg_capacity;

    bool is_path[3];    // Tells whether the given io file is a path or a fd
    void *io_files[3];  // input, output, and error output files
    int open_flags[3];  // options with which the file is opened if it's a path
} ast_command_t;


typedef struct {
    ast_type_t type;
    void *data;
} ast_t;


typedef void (*ast_delete_fnc_t)(void *data);


ast_t *ast_create(ast_type_t type);
void ast_delete(ast_t *ast);

// AST Utils:
void ast_print(const ast_t *ast);

// Implementation functions (need to be forward declared for double recursion)
void ast_print_node(const ast_t *ast, unsigned short depth);
void ast_delete_binop_data(void *data);

// Command:
ast_command_t *ast_command_create(void);
void ast_command_append(ast_command_t *command, const token_t *token);
void ast_command_delete(ast_command_t *command);


#endif
