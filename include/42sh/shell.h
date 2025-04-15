/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Header file for all things
** related to the shell
*/

#ifndef SHELL_SHELL_H
    #define SHELL_SHELL_H

    #define SH_EXEC_FAIL 1
    #define SH_SIGSEGV
    #define SHELL_RC_PATH "/.42shrc"

    #include <42sh/env.h>
    #include <sys/types.h>


// Shell runtime:
void shell_mainloop(sh_data_t *data);

// Shell system function:
void shell_system(const char *command, sh_data_t *data);

// Utils:
void shell_display_prompt(sh_data_t *data);
char *shell_query_input(sh_data_t *data);
char *shell_getcwd(sh_data_t *data, bool basename);
char *shell_get_command_abs_path(const char *command, sh_data_t *data);
int shell_run_file(sh_data_t *data, const char *path, char *args[]);
void shell_run_rc(sh_data_t *data);

// Command execution:
int shell_exec_command(char **args, sh_data_t *data);

// Subprocess (used by command execution):
pid_t shell_subprocess(char **args, sh_data_t *data);
void shell_setup_redirections(sh_data_t *data);
void shell_setup_pipe(sh_data_t *data);

// Signals:
void signal_init(sh_data_t *data);
void signal_interrupt_init(sh_data_t *data);
void signal_interrupt(int code);


// ---------- Shell Interpreter ---------- :
// Entry:
void *shell_interpret(ast_t *ast, sh_data_t *data);

// Program:
void *shell_interpret_program(ast_t *ast, sh_data_t *data);

// Expressions:
void *shell_interpret_operation_and(ast_t *ast, sh_data_t *data);
void *shell_interpret_operation_pipe(ast_t *ast, sh_data_t *data);
void *shell_interpret_operation_or(ast_t *ast, sh_data_t *data);

// Atom:
void *shell_interpret_command(ast_t *ast, sh_data_t *data);
void *shell_interpret_compound(ast_t *ast, sh_data_t *data);

// Sub-atom:
void *shell_interpret_argument(ast_t *ast, sh_data_t *data);
void *shell_interpret_redirect(ast_t *ast, sh_data_t *data);


#endif
