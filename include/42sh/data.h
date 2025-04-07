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


struct sh_data {
    // Variables:
    sh_symbols_t *local_vars;   // user local vars
    sh_symbols_t *env;          // user env
    sh_symbols_t *env_interal;  // internal copy of env

    // Redirections:
    int io_files[3];  // redirections
    int read_file;    // pipe in
    int write_file;   // pipe out

    // Process:
    pid_t prev_subproc;
    unsigned char exit_status;  // exit status of last exec (def: 0)
};


// Shell Data creation / deletion:
sh_data_t *sh_data_create(void);
void sh_data_delete(sh_data_t *data);
sh_data_t *sh_data_from_unix_env(char *envp[]);

// Shell Data utils:
const char *sh_data_getvar(sh_data_t *data, const char *name);


#endif
