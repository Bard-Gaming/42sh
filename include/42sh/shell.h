/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Header file for all things
** related to the shell
*/

#ifndef SHELL_SHELL_H
    #define SHELL_SHELL_H

    #define _GNU_SOURCE
    #define SH_PROGRAM_ERR 127

    #include <42sh/env.h>
    #include <sys/types.h>


// Main shell function:
void shell_mainloop(sh_data_t *data);

// Utils:
void shell_display_prompt(sh_data_t *data);
char *shell_query_input(sh_data_t *data);
char *shell_get_command_abs_path(const char *command, sh_data_t *env);

// Command execution:
int shell_exec_command(char **args, sh_data_t *data);

// Subprocess (used by command execution):
pid_t shell_subprocess(char **args, sh_data_t *data);
void shell_setup_redirections(sh_data_t *data);
void shell_setup_pipe(sh_data_t *data);


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
