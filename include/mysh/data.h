/*
** EPITECH PROJECT, 2024
** Project - 42sh
** File description:
** Header file for everything
** related to local shell data
*/

#ifndef MYSH_DATA_H
    #define MYSH_DATA_H
    #include <mysh/types.h>


enum sh_command_state {
    CS_NORMAL,  // keep first

    CS_PIPE_OUT,
    CS_PIPE_IN,
};

struct sh_data {
    sh_env_t *env;              // own env (def: NULL)
    unsigned char exit_status;  // exit status of last exec (def: 0)

    // Internal data:
    char *home_dir;
    char *previous_dir;

    // Redirections:
    sh_command_state_t cmd_state;
    int pipe_read;
    int pipe_write;
};


sh_data_t *sh_data_create(void);
void sh_data_delete(sh_data_t *data);
sh_data_t *sh_data_from_unix_env(char *envp[]);


#endif
