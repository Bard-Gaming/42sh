/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Header file for everything
** related to local shell data
*/

#ifndef MYSH_DATA_H
    #define MYSH_DATA_H

    #define IS_PIPE(data) (data->read_file != 0 || data->write_file != 1)

    #include <mysh/types.h>
    #include <sys/types.h>


struct sh_data {
    sh_env_t *env;              // own env (def: NULL)
    unsigned char exit_status;  // exit status of last exec (def: 0)

    // Internal data:
    char *home_dir;
    char *previous_dir;

    // Redirections:
    int io_files[3];  // redirections
    int read_file;    // pipe in
    int write_file;   // pipe out

    // Process:
    pid_t prev_subproc;
};


sh_data_t *sh_data_create(void);
void sh_data_delete(sh_data_t *data);
sh_data_t *sh_data_from_unix_env(char *envp[]);


#endif
