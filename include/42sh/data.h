/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Header file for everything
** related to local shell data
*/

#ifndef SHELL_DATA_H
    #define SHELL_DATA_H

    #define IS_PIPE(data) (data->read_file != 0 || data->write_file != 1)

    #include <42sh/types.h>
    #include <sys/types.h>
    #include <stdbool.h>
    #include <stdatomic.h>


struct sh_data {
    // Process:
    bool is_running;             // whether or not the shell is running
    pid_t prev_subproc;          // previous started subprocess
    char *shell_path;            // absolute path to shell binary
    char *prompt_str;            // parsed prompt string
    atomic_bool interrupt;       // interrupt signal handling

    // Command data:
    unsigned char exit_status;   // exit status of last exec (def: 0)
    bool success;                // used by the interpreter to tell status

    // Variables:
    sh_symbols_t *aliases;       // command aliases
    sh_symbols_t *local_vars;    // user local vars
    sh_symbols_t *env;           // user env
    sh_symbols_t *env_internal;  // internal copy of env

    // Redirections:
    bool should_close[3];        // tells which FDs need closing
    int io_files[3];             // FDs to use for stdin, stdout, and stderr
    int read_file;               // pipe in
    int write_file;              // pipe out
};


// Shell Data creation / deletion:
sh_data_t *sh_data_create(void);
void sh_data_delete(sh_data_t *data);
sh_data_t *sh_data_from_unix_env(char *envp[]);

// Shell Data utils:
const char *sh_data_getvar(const sh_data_t *data, const char *name);
void sh_data_setvar(sh_data_t *data, const char *name, const char *value);
void sh_data_setenv(sh_data_t *data, const char *name, const char *value);

// Shared:
void sh_data_register(sh_data_t *data);
sh_data_t *sh_data_get(void);

// Environment:
char **sh_env_create(const sh_data_t *data);
void sh_env_delete(char **env);


#endif
