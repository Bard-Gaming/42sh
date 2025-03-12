/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Header file for all things
** related to the shell
*/

#ifndef MYSH_SHELL_H
    #define MYSH_SHELL_H
    #define _GNU_SOURCE
    #include <mysh/env.h>
    #include <42parser/ast.h>
    #include <sys/types.h>
    #include <stdio.h>


typedef void (*sh_interpret_fnc_t)(ast_t *ast, sh_data_t *data);


void shell_mainloop(sh_data_t *data);
int shell_exec_command(char **args, sh_data_t *data);
void shell_interpret_input(ast_t *ast, sh_data_t *data);
pid_t shell_subprocess(const char *program, char **args, char **env);
char *shell_get_command_abs_path(const char *command, sh_env_t *env);
char *shell_query_input(void);


// ---------- Shell Interpreter ---------- :
// Entry:
void shell_interpret(ast_t *ast, sh_data_t *data);

// Atom:
void shell_interpret_command(ast_t *ast, sh_data_t *data);

// Operations:
void shell_interpret_command_chain(ast_t *ast, sh_data_t *data);
void shell_interpret_operation_and(ast_t *ast, sh_data_t *data);
void shell_interpret_operation_or(ast_t *ast, sh_data_t *data);


#endif
