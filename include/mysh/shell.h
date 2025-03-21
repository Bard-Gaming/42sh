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
    #include <sys/types.h>
    #include <stdio.h>


// Main shell function:
void shell_mainloop(sh_data_t *data);

// Utils:
char *shell_query_input(void);
char *shell_get_command_abs_path(const char *command, sh_env_t *env);

// Command execution:
int shell_exec_command(char **args, sh_data_t *data);
pid_t shell_subprocess(const char *program, char **args, sh_data_t *data);

// ---------- Shell Interpreter ---------- :
// Entry:
void shell_interpret(ast_t *ast, sh_data_t *data);

// Program:
void shell_interpret_program(ast_t *ast, sh_data_t *data);

// Statements:
void shell_interpret_operation_and(ast_t *ast, sh_data_t *data);
void shell_interpret_operation_pipe(ast_t *ast, sh_data_t *data);
void shell_interpret_operation_or(ast_t *ast, sh_data_t *data);

// Expression:
void shell_interpret_command(ast_t *ast, sh_data_t *data);


#endif
