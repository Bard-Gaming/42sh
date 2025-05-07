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
    #define SHELL_RC_PATH "/.42shrc"
    #define SHELL_HIST_PATH "/.42sh_history"
    #define SHELL_VERSION "1.0"

    #include <42sh/types.h>
    #include <sys/types.h>


// Shell runtime:
void shell_mainloop(sh_data_t *data);

// Shell system function:
void shell_system(const char *command, sh_data_t *data);

// Utils:
char *shell_query_input(sh_data_t *data);
char *shell_history(size_t index);
void sh_history_add_line(const char *line);
char *shell_autocomplete(const char *input);
char *shell_getcwd(const sh_data_t *data, bool basename);
char *shell_get_command_abs_path(const char *command, sh_data_t *data);
int shell_run_file(sh_data_t *data, const char *path, char *args[]);
void shell_run_rc(sh_data_t *data);
void shell_update_prompt(sh_data_t *data);
char *shell_alias(const char *command);

// Command execution:
int shell_exec_command(char **args, sh_data_t *data);

// Subprocess (used by command execution):
pid_t shell_subprocess(char **args, sh_data_t *data);
void shell_setup_redirections(sh_data_t *data);
void shell_setup_pipe(sh_data_t *data);

// Signals:
void signal_init(void);
void signal_interrupt(int code);

// History:
char *shell_history_get(size_t index);
void shell_history_add(const char *command);

// Init:
void shell_init(sh_data_t *data);


// ---------- Shell Interpreter ---------- :
// Entry:
void shell_interpret(ast_t *ast, sh_data_t *data);
void shell_interpret_value(ast_t *ast, sh_data_t *data, sh_vector_t *argv);

// Program:
void shell_interpret_program(ast_t *ast, sh_data_t *data);

// Statements:
void shell_interpret_while_loop(ast_t *ast, sh_data_t *data);
void shell_interpret_if_statement(ast_t *ast, sh_data_t *data);

// Expressions:
void shell_interpret_operation_and(ast_t *ast, sh_data_t *data);
void shell_interpret_operation_pipe(ast_t *ast, sh_data_t *data);
void shell_interpret_operation_or(ast_t *ast, sh_data_t *data);

// Atom:
void shell_interpret_command(ast_t *ast, sh_data_t *data);
void shell_interpret_compound(ast_t *ast, sh_data_t *data);

// Sub-atom:
void shell_interpret_redirect(ast_t *ast, sh_data_t *data,
    sh_vector_t *argv);
void shell_interpret_argument_str(ast_t *ast, sh_data_t *data,
    sh_vector_t *argv);
void shell_interpret_argument(ast_t *ast, sh_data_t *data,
    sh_vector_t *argv);
void shell_interpret_substitution(ast_t *ast, sh_data_t *data,
    sh_vector_t *argv);
void shell_interpret_raw_argument(ast_t *ast, sh_data_t *data,
    sh_vector_t *argv);
void shell_interpret_variable(ast_t *ast, sh_data_t *data,
    sh_vector_t *argv);


// Helper functions:
bool shell_interpret_condition(ast_condition_t *condition, sh_data_t *data);


#endif
